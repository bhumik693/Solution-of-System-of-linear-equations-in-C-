#ifndef INF_POS_CHANGES_H
#define INF_POS_CHANGES_H

#include <iostream>
#include <stack>
#include <queue>
#include <string>
#include <math.h>
using namespace std;

#define SIZE 26
void zero(double *arr);
void filling_array(string input, int equation_no, int &no_of_variables, int *variables_poisiton, double *arr, queue<double> &nums_value);
void input_series(double *arr, queue<double> &nums_value, int &equation_no, int &no_of_variables);
void final_array(double *augmented_matrix, queue<double> &nums_value, int equation_no, int no_of_variables);
int is_operator(char input);
int precedence(char input);
double infix_to_postfix(string input);
double ans(queue<string> postfix);
double calculation(double operand_1, double operand_2, string str);

#endif