#include <iostream>
#include <stack>
#include <queue>
#include <string>
#include <math.h>
#include "infix_postfix.h"
using namespace std;

/*#define SIZE 26
void zero(double *arr);
void filling_array(string &input, int equation_no, int &no_of_variables, int *variables_poisiton, double *arr, queue<double> &nums_value);
void input_series(double *arr, queue<double> &nums_value, int &equation_no, int &no_of_variables);
void final_array(double *augmented_matrix, queue<double> &nums_value, int equation_no, int no_of_variables);
int is_operator(char input);
int precedence(char input);
double infix_to_postfix(string input);
double ans(queue<string> postfix);
double calculation(double operand_1, double operand_2, string str);*/

int main()
{
    double arr[SIZE];
    int equation_no = 0;
    int no_of_variables = 0;
    queue<double> nums_value;
    input_series(arr, nums_value, equation_no, no_of_variables);
    double augmented_matrix[equation_no][no_of_variables + 1];
    final_array(*augmented_matrix, nums_value, equation_no, no_of_variables);
    cout << augmented_matrix[0][0] << " " << augmented_matrix[0][1] << " " << augmented_matrix[0][2] << endl;
    cout << augmented_matrix[1][0] << " " << augmented_matrix[1][1] << " " << augmented_matrix[1][2] << endl;
    // cout << augmented_matrix[2][0] << " " << augmented_matrix[2][1] << " " << augmented_matrix[2][2] << endl;
    return 0;
}

void final_array(double *augmented_matrix, queue<double> &nums_value, int equation_no, int no_of_variables)
{
    int i;
    int j = 0;
    double prev;
    for (i = 0; i < equation_no; i++)
    {
        for (j = 0; j < no_of_variables + 1; j++)
        {

            if (nums_value.front() != INT_MIN)
            {
                prev = nums_value.front();
                *(augmented_matrix + i * (no_of_variables + 1) + j) = nums_value.front();
                nums_value.pop();
            }
            else
            {
                *(augmented_matrix + i * (no_of_variables + 1) + j - 1) = 0;
            }
        }
        nums_value.pop();
        *(augmented_matrix + i * (no_of_variables + 1) + no_of_variables) = prev;
    }
}

void zero(double *arr)
{
    int i, j;
    for (i = 0; i < SIZE; i++)
    {
        arr[i] = 0;
    }
}

void input_series(double *arr, queue<double> &nums_value, int &equation_no, int &no_of_variables)
{
    string input = "";
    int i;

    int variables_poisiton[SIZE];
    for (i = 0; i < SIZE; i++)
    {
        variables_poisiton[i] = -1;
    }

    zero(arr);
    getline(cin, input);
    // cin >> input;
    while (input != "quit")
    {
        zero(arr);
        filling_array(input, equation_no, no_of_variables, variables_poisiton, arr, nums_value);
        equation_no = equation_no + 1;
        getline(cin, input);
    }
    cout << "no_of_variables " << no_of_variables << endl;
}

void filling_array(string input, int equation_no, int &no_of_variables, int *variables_poisiton, double *arr, queue<double> &nums_value)
{
    int i;
    int variable_found_status = 0;
    int lhs_status = 1;
    int bracket_status = 1;
    int equal_status = 0;

    // int no_of_variables = 0;
    string num_string = "";
    double num;
    double b_value = 0;
    int num_status;
    int length = input.length();
    cout << length << endl;
    // int variables_poisiton[SIZE];
    stack<char> bracket_close;
    /*for (i = 0; i < SIZE; i++)
    {
        variables_poisiton[i] = -1;
    }*/

    cout << input[0] << endl;
    for (i = 0; i < length; i++)
    {
        // cout << "input " << i << " " << input[i] << endl;
        // cout << "num_String " << num_string << endl;
        // cout << "variable status " << variable_found_status << endl;
        if (input[i] >= 97 && input[i] <= 122)
        {
            // infix_to_postfix_call
            if (i == 0 || equal_status == 1)
            {
                num_string = "1";
            }
            equal_status = 0;
            bracket_status = 1;
            variable_found_status = 1;
            // cout << "variable status " << variable_found_status << endl;
            while (!bracket_close.empty())
            {
                bracket_close.pop();
            }
            num = infix_to_postfix(num_string);
            //  cout << "bye" << endl;
            if (variables_poisiton[input[i] - 97] == -1)
            {
                // cout << "go" << endl;
                variables_poisiton[input[i] - 97] = no_of_variables;
                no_of_variables = no_of_variables + 1;
            }
            // cout << "variable " << variables_poisiton[input[i] - 97] << endl;
            // cout << "num " << num << endl;
            if (lhs_status == 1)
            {
                // cout << "before " << *(arr + SIZE * equation_no + variables_poisiton[input[i] - 97]) << endl;
                //*(arr + SIZE * equation_no + variables_poisiton[input[i] - 97]) = *(arr + SIZE * equation_no + variables_poisiton[input[i] - 97]) + num;
                // cout << "after " << *(arr + SIZE * equation_no + variables_poisiton[input[i] - 97]) << endl;
                arr[variables_poisiton[input[i] - 97]] = arr[variables_poisiton[input[i] - 97]] + num;
            }
            else
            {
                //*(arr + SIZE * equation_no + variables_poisiton[input[i] - 97]) = *(arr + SIZE * equation_no + variables_poisiton[input[i] - 97]) - num;
                arr[variables_poisiton[input[i] - 97]] = arr[variables_poisiton[input[i] - 97]] - num;
            }
            num_string = "";
            // cout << "go " << num_string << endl;
            // cout << "variable status " << variable_found_status << endl;
        }
        else if ((input[i] >= 48 && input[i] <= 57) || input[i] == '(' || input[i] == ')' || input[i] == '{' || input[i] == '}' || input[i] == '[' || input[i] == ']' || input[i] == '.')
        {
            equal_status = 0;
            variable_found_status = 0;
            num_string.push_back(input[i]);
            if (input[i] == '(' || input[i] == '{' || input[i] == '[')
            {
                bracket_status = 1;
                bracket_close.push(input[i]);
            }
            if (input[i] == ')' || input[i] == '}' || input[i] == ']')
            {
                if (!bracket_close.empty())
                {
                    bracket_close.pop();
                }
            }
            if (bracket_close.empty())
            {
                bracket_status = 0;
            }
        }
        else if ((input[i] == '+' || input[i] == '-'))
        {
            equal_status = 0;
            variable_found_status = 0;
            if (bracket_status == 0)
            {
                num = infix_to_postfix(num_string);
                if (lhs_status == 1)
                {
                    b_value = b_value - num;
                }
                else
                {
                    b_value = b_value + num;
                }
                while (!bracket_close.empty())
                {
                    bracket_close.pop();
                }
                num_string = "";
                num_string.push_back(input[i]);
            }
            else
            {
                num_string.push_back(input[i]);
            }
        }
        else if (input[i] == '=')
        {
            equal_status = 1;
            if (variable_found_status == 0)
            {
                // cout << "ythi" << endl;
                num = infix_to_postfix(num_string);
                // cout << "num " << num << endl;
                if (lhs_status == 1)
                {
                    b_value = b_value - num;
                }
                else
                {
                    b_value = b_value + num;
                }
            }

            /*if (lhs_status == 1)
            {
                *(arr + SIZE * equation_no + variables_poisiton[input[i] - 97]) = *(arr + SIZE * equation_no + variables_poisiton[input[i] - 97]) + num;
            }
            else
            {
                *(arr + SIZE * equation_no + variables_poisiton[input[i] - 97]) = *(arr + SIZE * equation_no + variables_poisiton[input[i] - 97]) - num;
            }*/
            num_string = "";
            lhs_status = 0;
        }
    }
    for (i = 0; i < no_of_variables; i++)
    {
        cout << "queue " << arr[i] << endl;
        nums_value.push(arr[i]);
    }
    if (lhs_status == 1)
    {
        cout << "Wrong input" << endl;
        exit(1);
    }
    if (variable_found_status == 0)
    {
        num = infix_to_postfix(num_string);
        b_value = b_value + num;
        nums_value.push(b_value);
    }
    nums_value.push(INT_MIN);
    // cout << "b value " << b_value << endl;
}
