#ifndef INF_POS_CHANGES_H
#define INF_POS_CHANGES_H

#include <iostream>
#include <stack>
#include <queue>
#include <string>
#include <math.h>
using namespace std;

#define SIZE 26
void solution_equations(double *augmented_matrix, int no_of_variables, int no_of_equations);
int first_element_non_zero_row(double *arr, int no_of_equations, int no_of_variables, int column);
void swapping_of_zeroth_row_with_non_zeroth_row(double *arr, int no_of_equations, int no_of_variables, int first_element_non_zeroth_row_index, int column);
void row_echelon_form(double *arr, int no_of_equations, int no_of_variables, int column);
void row_reduced_echelon_form(double *arr, int no_of_equations, int no_of_variables, int column);
int pivot_column(double *arr, int no_of_variables, int row);
int pivots(double *arr, int no_of_equations, int no_of_variables);
void zero(double *arr);
int filling_array(string input, int equation_no, int &no_of_variables, int *variables_poisiton, double *arr, queue<double> &nums_value);
void input_series(double *arr, queue<double> &nums_value, int &equation_no, int &no_of_variables);
void final_array(double *augmented_matrix, queue<double> &nums_value, int equation_no, int no_of_variables);
int is_operator(char input);
int precedence(char input);
double infix_to_postfix(string input);
double ans(queue<string> postfix);
double calculation(double operand_1, double operand_2, string str);

#endif