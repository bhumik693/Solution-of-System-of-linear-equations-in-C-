#ifndef LINEAR_EQUATIONS_H
#define LINEAR_EQUATIONS_H

#include <iostream>
int pivot_column(double *arr, int no_of_variables, int row);
int pivots(double *arr, int no_of_equations, int no_of_variables);
void arr_initializer(double *arr, int no_of_equations, int no_of_varaibles);
int first_element_non_zero_row(double *arr, int no_of_equations, int no_of_variables, int column);
void swapping_of_zeroth_row_with_non_zeroth_row(double *arr, int no_of_equations, int no_of_variables, int first_element_non_zeroth_row_index, int column);
void row_echelon_form(double *arr, int no_of_equations, int no_of_variables, int column);
void row_reduced_echelon_form(double *arr, int no_of_equations, int no_of_variables, int column);
#endif