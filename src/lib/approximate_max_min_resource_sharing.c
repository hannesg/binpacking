/******************************************************************************
 * Authors:
 * 2011 Bastian Holst <bastianholst@gmx.de>
 *****************************************************************************/

// Standard library
#include <stdlib.h>
#include <math.h>

// Library
#include "approximate_block_solver.h"
#include "double_vector.h"
#include "double_matrix.h"
#include "uint_matrix.h"
#include "knapsack.h"
#include "packing_list.h"

// Self
#include "approximate_max_min_resource_sharing.h"
#include "approximate_max_min_resource_sharing_p.h"

void free_max_min_resource_sharing_solution(max_min_resource_sharing_solution *solution)
{
    if(solution == NULL) {
        return;
    }
    free_double_vector(solution->vector);
    free_double_vector(solution->function_solution);
    free(solution);
}

double calculate_optimum_condition(double_vector *b, double theta, double t)
{
    double result = 0;
    
    int i;
    for(i = 0; i < b->size; ++i) {
        result += theta / (b->values[i] - theta);
    }
    
    result = result * t/((double) b->size);
    
    return result;
}

double find_optimum(double_vector *b, double t)
{
    double minimum = 0;
    double maximum = vector_min(b);
    
    double medium = 0.5 * (minimum + maximum);
    double optimum_condition = calculate_optimum_condition(b, medium, t);
    while(fabs(optimum_condition - 1) > 1e-10 && minimum < maximum) { 
        // Intervallgroeße 1/8 * (epsilon^2 / M)
        if(optimum_condition < 1) {
            minimum = medium;
        } else {
            maximum = medium;
        }
        
        medium = 0.5 * (minimum + maximum);
        optimum_condition = calculate_optimum_condition(b, medium, t);
    }
    
    return medium;
}

max_min_resource_sharing_solution *approximate_max_min_resource_sharing(double_matrix *A,
                                                                        unsigned int limit,
                                                                        double precision)
{
    // The vector to contain the solution.
    double_vector *x = alloc_double_vector(A->height);
    fill_double_vector(x, 0.0);
    
    // A vector needed to compute the starting solution.
    double_vector *p = alloc_double_vector(A->width);
    fill_double_vector(p, 0.0);

    // Compute the starting solution.
    int m;
    for(m = 0; m < A->width; m++) {
        p->values[m] = 1.0;
        double_vector *block_solution = approximate_block_solver(A, p, limit, 0.5);
        vector_vector_add_assignment(x, block_solution);
        free_double_vector(block_solution);
        p->values[m] = 0.0;
    }
    // Vector p will stay in memory, it is needed in the while-loop.
    number_vector_mult_assignment(1.0/((double) A->width), x);
    
    double approximate_block_solver_precision = precision / 6;
    
    double_vector *function_solution = transposed_matrix_vector_mult(A, x);
    while(1) {
        double theta = find_optimum(function_solution, approximate_block_solver_precision);
        
        // Calculation p
        int i;
        for(i = 0; i < function_solution->size; ++i) {
            // the vector p is already in memory with the right size
            p->values[i] =
                approximate_block_solver_precision / ((double) function_solution->size)
                * theta / (function_solution->values[i] - theta);
        }
        
        // Calculating the hat x
        double_vector *hat_x = approximate_block_solver(A, p, limit,
                                                        approximate_block_solver_precision);
        double_vector *hat_function_solution = transposed_matrix_vector_mult(A, hat_x);
        
        // Checking what we want to do next
        double hat_prod = vector_scalar_mult(p, hat_function_solution);
        double prod = vector_scalar_mult(p, function_solution);
        double residuum = (hat_prod - prod) / (hat_prod + prod);
        
        if(fabs(residuum) < approximate_block_solver_precision) {
            free_double_vector(hat_x);
            free_double_vector(hat_function_solution);
            break;
        }
        
        // Calculate step size
        double step_size = (approximate_block_solver_precision * theta * residuum)
                           / (2 * A->width * (hat_prod + prod));
        
        number_vector_mult_assignment(1 - step_size, x);
        number_vector_mult_assignment(step_size, hat_x);
        vector_vector_add_assignment(x, hat_x);
        
        free_double_vector(hat_x);
        
        vector_convex_assignment(function_solution, hat_function_solution, step_size );

        free_double_vector(hat_function_solution);
    }
    
    free_double_vector(p);
    
    max_min_resource_sharing_solution *result
        = (max_min_resource_sharing_solution *) malloc(sizeof(max_min_resource_sharing_solution));
    result->vector = x;
    result->function_solution = function_solution;
    result->function_solution_min = vector_min(function_solution);
    
    return result;
}

max_min_resource_sharing_solution *approximate_rbp_lp_max_min_resource_sharing(double_vector *items,
                                                                        uint_matrix *A,
                                                                        unsigned int k,
                                                                        unsigned int limit,
                                                                        double precision
                                                                        )
{
    // M is the number of items, which is equal to the width of the matrix
    unsigned int M = items->size;

    // The vector to contain the solution.
    double_vector *x = alloc_double_vector(A->height);
    fill_double_vector(x, 0.0);

    // A vector needed to compute the starting solution.
    double_vector *p = alloc_double_vector(M);
    fill_double_vector(p, 0.0);

    // Compute the starting solution.
    // TODO: the starting solution is constant inside an LP-solver
    int m;
    for(m = 0; m < M; m++) {
        p->values[m] = 1.0;
        double_vector *block_solution = approximate_bound_knapsack_block_solver(A, items, p, PACKING_SIZE, k, limit, 0.5);
        vector_vector_add_assignment(x, block_solution);
        free_double_vector(block_solution);
        p->values[m] = 0.0;
    }

    // Vector p will stay in memory, it is needed in the while-loop.
    number_vector_mult_assignment(1.0/((double) M), x);

    double approximate_block_solver_precision = (precision / 6);

    double_vector *function_solution = uint_transposed_matrix_vector_mult(A, x);
    int iter_count = 1;
    while(1) {
        double theta = find_optimum(function_solution, approximate_block_solver_precision);

        // Calculation p
        int i;
        for(i = 0; i < function_solution->size; ++i) {
            // the vector p is already in memory with the right size
            p->values[i] =
                approximate_block_solver_precision / ((double) function_solution->size)
                * theta / (function_solution->values[i] - theta);
        }

        // Calculating the hat x
        double_vector *hat_x = approximate_bound_knapsack_block_solver(A, items, p, PACKING_SIZE, k, limit,
                                                        approximate_block_solver_precision);
        double_vector *hat_function_solution = uint_transposed_matrix_vector_mult(A, hat_x);

        // Checking what we want to do next
        double hat_prod = vector_scalar_mult(p, hat_function_solution);
        double prod = vector_scalar_mult(p, function_solution);
        double residuum = (hat_prod - prod) / (hat_prod + prod);
        
        printf("Iteration %i, residuum %lf.\r", iter_count, residuum);

        if(fabs(residuum) < approximate_block_solver_precision) {
            free_double_vector(hat_x);
            free_double_vector(hat_function_solution);
            break;
        }

        // Calculate step size
        double step_size = (approximate_block_solver_precision * theta * residuum)
                           / (2 * M * (hat_prod + prod));

        number_vector_mult_assignment(1 - step_size, x);
        number_vector_mult_assignment(step_size, hat_x);
        vector_vector_add_assignment(x, hat_x);

        free_double_vector(hat_x);

        vector_convex_assignment(function_solution, hat_function_solution, step_size );

        free_double_vector(hat_function_solution);
        iter_count++;
    }
    printf("Needed %i iterations.\n", iter_count);

    free_double_vector(p);

    max_min_resource_sharing_solution *result
        = (max_min_resource_sharing_solution *) malloc(sizeof(max_min_resource_sharing_solution));
    result->vector = x;
    result->function_solution = function_solution;
    result->function_solution_min = vector_min(function_solution);

    return result;
}
