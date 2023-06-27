#include <iostream>
#include <stack>
#include <queue>
#include <string>
#include <math.h>
#include <climits>
#include "infix_postfix.h"
using namespace std;

int main()
{
    double arr[SIZE];
    int no_of_equations = 0;
    int no_of_variables = 0;
    queue<double> nums_value;
    input_series(arr, nums_value, no_of_equations, no_of_variables);
    double augmented_matrix[no_of_equations][no_of_variables + 1];
    final_array(*augmented_matrix, nums_value, no_of_equations, no_of_variables);
    solution_equations(*augmented_matrix, no_of_variables, no_of_equations);
    return 0;
}

void solution_equations(double *augmented_matrix, int no_of_variables, int no_of_equations)
{
    int no_of_pivots;
    if (no_of_equations <= no_of_variables)
    {
        int i, j;
        row_echelon_form(augmented_matrix, no_of_equations, no_of_variables, 0);
        no_of_pivots = pivots(augmented_matrix, no_of_equations, no_of_variables);
        if (no_of_pivots == no_of_variables)
        {
            row_reduced_echelon_form(augmented_matrix, no_of_equations, no_of_variables, 1);
            for (i = 0; i < no_of_equations; i++)
            {
                for (j = 0; j < no_of_variables + 1; j++)
                {
                    cout.precision(2);
                    cout << fixed << *(augmented_matrix + (no_of_variables + 1) * i + j) << " ";
                }
                cout << endl;
            }
        }
        else
        {
            cout << "Infinite Solutions" << endl;
        }
    }
    else
    {
        cout << "Cant find solution" << endl;
    }
}

int first_element_non_zero_row(double *arr, int no_of_equations, int no_of_variables, int column)
{
    int i;
    int non_zeroth_row = -1;
    for (i = column; i < no_of_equations; i++)
    {
        if (*(arr + i * (no_of_variables + 1) + column) != 0)
        {
            non_zeroth_row = i;
        }
    }
    return non_zeroth_row;
}

void swapping_of_zeroth_row_with_non_zeroth_row(double *arr, int no_of_equations, int no_of_variables, int first_element_non_zeroth_row_index, int column)
{
    int j;
    double temp;
    for (j = 0; j < no_of_variables + 1; j++)
    {
        temp = *(arr + column * (no_of_variables + 1) + j);
        *(arr + column * (no_of_variables + 1) + j) = *(arr + first_element_non_zeroth_row_index * (no_of_variables + 1) + j);
        *(arr + first_element_non_zeroth_row_index * (no_of_variables + 1) + j) = temp;
    }
}

void row_echelon_form(double *arr, int no_of_equations, int no_of_variables, int column)
{
    if (column != no_of_equations)
    {
        int k;
        double t;
        int i, j;
        k = first_element_non_zero_row(arr, no_of_equations, no_of_variables, column);
        if (k != -1)
        {
            swapping_of_zeroth_row_with_non_zeroth_row(arr, no_of_equations, no_of_variables, k, column);
        }
        double extra = *(arr + column * (no_of_variables + 1) + column);
        if (extra != 0)
        {
            for (i = 0; i < no_of_variables + 1; i++)
            { // converting no. to 1
                *(arr + column * (no_of_variables + 1) + i) = (*(arr + column * (no_of_variables + 1) + i)) / (extra);
            }
        }
        for (i = column + 1; i < no_of_equations; i++)
        { // making echlon form
            t = (*(arr + i * (no_of_variables + 1) + column));
            for (j = 0; j < no_of_variables + 1; j++)
            {
                *(arr + i * (no_of_variables + 1) + j) = *(arr + i * (no_of_variables + 1) + j) - t * (*(arr + column * (no_of_variables + 1) + j));
            }
        }
        row_echelon_form(arr, no_of_equations, no_of_variables, column + 1);
    }
}

void row_reduced_echelon_form(double *arr, int no_of_equations, int no_of_variables, int column)
{
    if (column != no_of_equations)
    {
        int i, j;
        float t;
        // int extra = *(arr+column*(n+1)+column);
        for (i = column - 1; i >= 0; i--)
        {
            t = (*(arr + i * (no_of_variables + 1) + column));
            for (j = 0; j < no_of_variables + 1; j++)
            {
                *(arr + i * (no_of_variables + 1) + j) = *(arr + i * (no_of_variables + 1) + j) - t * (*(arr + column * (no_of_variables + 1) + j));
            }
        }
        row_reduced_echelon_form(arr, no_of_equations, no_of_variables, column + 1);
    }
}

int pivot_column(double *arr, int no_of_variables, int row)
{
    int column = -1;
    int i;
    int flag_exit = 0;
    for (i = 0; i < no_of_variables && flag_exit == 0; i++)
    {
        if (*(arr + row * (no_of_variables + 1) + i) != 0)
        {
            column = i;
            flag_exit = 1;
        }
    }
    return column;
}

int pivots(double *arr, int no_of_equations, int no_of_variables)
{
    // int pivots[no_of_variables];
    int i, j, k;
    int no_of_pivots = 0;
    int pivot;
    for (i = 0; i < no_of_equations; i++)
    {
        pivot = pivot_column(arr, no_of_variables, i);
        if (pivot != -1)
        {
            no_of_pivots = no_of_pivots + 1;
        }
    }
    return no_of_pivots;
}

void final_array(double *augmented_matrix, queue<double> &nums_value, int no_of_equations, int no_of_variables)
{
    int i;
    int j = 0;
    double prev;
    for (i = 0; i < no_of_equations; i++)
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

void input_series(double *arr, queue<double> &nums_value, int &no_of_equations, int &no_of_variables)
{
    string input = "";
    int i;
    int variables_poisiton[SIZE];
    int wrong_input;
    for (i = 0; i < SIZE; i++)
    {
        variables_poisiton[i] = -1;
    }
    cout << "Please enter your equation. If completed enter quit" << endl;
    cout << "Equation no " << no_of_equations + 1 << endl;
    zero(arr);
    getline(cin, input);
    // cin >> input;
    while (input != "quit")
    {
        zero(arr);
        wrong_input = filling_array(input, no_of_equations, no_of_variables, variables_poisiton, arr, nums_value);
        if (wrong_input == 0)
        {
            no_of_equations = no_of_equations + 1;
        }
        cout << "Equation no " << no_of_equations + 1 << endl;
        getline(cin, input);
    }
}

string single_input()
{
    string input = "";
    getline(cin, input);
    return input;
}

int filling_array(string input, int no_of_equations, int &no_of_variables, int *variables_poisiton, double *arr, queue<double> &nums_value)
{
    int i;
    int variable_found_status = 0;
    int lhs_status = 1;
    int bracket_status = 1;
    int equal_status = 0;
    int exit_status = 0;
    // int no_of_variables = 0;
    string num_string = "";
    double num;
    double b_value = 0;
    int num_status;
    int length = input.length();
    // int variables_poisiton[SIZE];
    stack<char> bracket_close;
    for (i = 0; i < length && exit_status == 0; i++)
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
            if (num != INT_MIN)
            {
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
                    // cout << "before " << *(arr + SIZE * no_of_equations + variables_poisiton[input[i] - 97]) << endl;
                    //*(arr + SIZE * no_of_equations + variables_poisiton[input[i] - 97]) = *(arr + SIZE * no_of_equations + variables_poisiton[input[i] - 97]) + num;
                    // cout << "after " << *(arr + SIZE * no_of_equations + variables_poisiton[input[i] - 97]) << endl;
                    arr[variables_poisiton[input[i] - 97]] = arr[variables_poisiton[input[i] - 97]] + num;
                }
                else
                {
                    //*(arr + SIZE * no_of_equations + variables_poisiton[input[i] - 97]) = *(arr + SIZE * no_of_equations + variables_poisiton[input[i] - 97]) - num;
                    arr[variables_poisiton[input[i] - 97]] = arr[variables_poisiton[input[i] - 97]] - num;
                }
                num_string = "";
                // cout << "go " << num_string << endl;
                // cout << "variable status " << variable_found_status << endl;
            }
            else
            {
                exit_status = 1;
            }
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
                if (num != INT_MIN)
                {
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
                    exit_status = 1;
                }
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
                if (num != INT_MIN)
                {
                    if (lhs_status == 1)
                    {
                        b_value = b_value - num;
                    }
                    else
                    {
                        b_value = b_value + num;
                    }
                }
                else
                {
                    exit_status = 1;
                }
            }
            num_string = "";
            lhs_status = 0;
        }
    }
    if (exit_status == 0)
    {
        for (i = 0; i < no_of_variables; i++)
        {
            nums_value.push(arr[i]);
        }
        if (lhs_status == 1)
        {
            cout << "Wrong input" << endl;
            exit_status = 1;
        }
        else
        {
            if (variable_found_status == 0)
            {
                num = infix_to_postfix(num_string);
                b_value = b_value + num;
                nums_value.push(b_value);
            }
            nums_value.push(INT_MIN);
        }
    }
    return exit_status;
    // cout << "b value " << b_value << endl;
}

int is_operator(char input)
{
    int ans = 0;
    if (input == '*' || input == '/' || input == '-' || input == '+' || input == '(' || input == ')' || input == '{' || input == '}' || input == '[' || input == ']')
    {
        ans = 1;
    }
    else if (input >= 48 && input <= 57 || input == '.')
    {
        ans = 0;
    }
    else
    {
        ans = 2;
    }
    return ans;
}

int precedence(char input)
{
    int ans;
    if (input == '*' || input == '/')
    {
        ans = 4;
    }
    else if (input == '+' || input == '-')
    {
        ans = 3;
    }
    else if (input == '(')
    {
        ans = 2;
    }
    else if (input == '{')
    {
        ans = 1;
    }
    else if (input == '[')
    {
        ans = 0;
    }

    return ans;
}

double infix_to_postfix(string input)
{
    queue<string> postfix;
    int i;
    double temp = 0;
    int num_status = 0;
    int operator_status = 1;
    int mul_div_bracket_status = 1;
    int add_sub_status = 0;
    int exit_status = 0;
    int sign = 1;
    string temp_string;
    char operator_string[2];
    int decimal = 0;
    stack<char> s;
    double t = INT_MIN;
    for (i = 0; i < input.length() && exit_status == 0; i++)
    {
        // cout << i << "  " << input[i] << endl;
        /*if (input == "+")
        {
            cout << "hi" << i << endl;
            temp = 0;
            temp_string = to_string(temp);
            postfix.push(temp_string);
        }
        if (input == "-")
        {
            temp = -1;
            temp_string = to_string(temp);
            postfix.push(temp_string);
        }*/
        if (input[i] != ' ')
        {
            if (is_operator(input[i]) == 0)
            {
                num_status = 1;
                // operator_status = 0;
                mul_div_bracket_status = 0;
                add_sub_status = 0;
                if (input[i] != '.' && decimal == 0)
                {
                    temp = temp * 10 + int(input[i]) - 48;
                }
                else if (input[i] != '.')
                {
                    temp = temp + (input[i] - 48) * pow(0.1, decimal);
                    decimal++;
                }
                else
                {
                    decimal++;
                }
            }
            else if (is_operator(input[i]) == 2)
            {
                cout << "Wrong input" << endl;
                exit_status = 1;
            }
            else if (input[i] == ')')
            {
                decimal = 0;
                // decimal_status = 0;
                if (num_status == 1)
                {
                    temp_string = to_string(sign * temp);
                    postfix.push(temp_string);
                    num_status = 0;
                }
                sign = 1;
                if (mul_div_bracket_status == 1 || add_sub_status == 1)
                {
                    cout << "Wrong input" << endl;
                    exit_status = 1;
                }
                else
                {
                    while (!s.empty() && s.top() != '(' && exit_status == 0)
                    {
                        operator_string[0] = s.top();
                        operator_string[1] = '\0';
                        postfix.push(operator_string);
                        s.pop();
                        if (s.empty())
                        {
                            cout << "Wrong input" << endl;
                            exit_status = 1;
                        }
                    }
                    if (exit_status == 0)
                    {
                        if (s.empty())
                        {
                            cout << "Wrong input" << endl;
                            exit_status = 1;
                        }
                        else
                        {
                            s.pop();
                        }
                    }
                }
            }
            else if (input[i] == '(')
            {
                decimal = 0;
                if (num_status == 1)
                {
                    temp_string = to_string(sign * temp);
                    postfix.push(temp_string);
                    num_status = 0;
                }
                // operator_status = 1;
                if (add_sub_status == 1 || mul_div_bracket_status == 1)
                {
                    temp = 1;
                    temp_string = to_string(sign * temp);
                    postfix.push(temp_string);
                    add_sub_status = 0;
                    mul_div_bracket_status = 0;
                }
                add_sub_status = 0;
                mul_div_bracket_status = 1;
                sign = 1;
                s.push('*');
                s.push(input[i]);
                if (i != input.length())
                {
                    temp = 0;
                }
            }
            else if (input[i] == '}')
            {
                decimal = 0;
                // decimal_status = 0;
                if (num_status == 1)
                {
                    temp_string = to_string(sign * temp);
                    postfix.push(temp_string);
                    num_status = 0;
                }
                sign = 1;
                if (mul_div_bracket_status == 1 || add_sub_status == 1)
                {
                    cout << "Wrong input" << endl;
                    exit(1);
                }
                else
                {
                    while (!s.empty() && s.top() != '{' && exit_status == 0)
                    {
                        operator_string[0] = s.top();
                        operator_string[1] = '\0';
                        postfix.push(operator_string);
                        s.pop();
                        if (s.empty() || operator_string[0] == '(')
                        {
                            cout << "Wrong input" << endl;
                            exit_status = 1;
                        }
                    }
                    if (exit_status == 0)
                    {
                        if (s.empty())
                        {
                            cout << "Wrong input" << endl;
                            exit_status = 1;
                        }
                        else
                        {
                            s.pop();
                        }
                    }
                }
            }
            else if (input[i] == '{')
            {
                decimal = 0;
                if (num_status == 1)
                {
                    temp_string = to_string(sign * temp);
                    postfix.push(temp_string);
                    num_status = 0;
                }
                // operator_status = 1;
                if (add_sub_status == 1 || mul_div_bracket_status == 1)
                {
                    temp = 1;
                    temp_string = to_string(sign * temp);
                    postfix.push(temp_string);
                    add_sub_status = 0;
                    mul_div_bracket_status = 0;
                }
                add_sub_status = 0;
                mul_div_bracket_status = 1;
                sign = 1;
                s.push('*');
                s.push(input[i]);
                if (i != input.length())
                {
                    temp = 0;
                }
            }
            else if (input[i] == ']')
            {
                decimal = 0;
                // decimal_status = 0;
                if (num_status == 1)
                {
                    temp_string = to_string(sign * temp);
                    postfix.push(temp_string);
                    num_status = 0;
                }
                sign = 1;
                if (mul_div_bracket_status == 1 || add_sub_status == 1)
                {
                    cout << "Wrong input" << endl;
                    exit(1);
                }
                else
                {
                    while (!s.empty() && s.top() != '[' && exit_status == 0)
                    {
                        operator_string[0] = s.top();
                        operator_string[1] = '\0';
                        postfix.push(operator_string);
                        s.pop();
                        if (s.empty() || operator_string[0] == '(' || operator_string[0] == '{')
                        {
                            cout << "Wrong input" << endl;
                            exit_status = 1;
                        }
                    }
                    if (exit_status == 0)
                    {
                        if (s.empty())
                        {
                            cout << "Wrong input" << endl;
                            exit(1);
                        }
                        else
                        {
                            s.pop();
                        }
                    }
                }
            }
            else if (input[i] == '[')
            {
                decimal = 0;
                if (num_status == 1)
                {
                    temp_string = to_string(sign * temp);
                    postfix.push(temp_string);
                    num_status = 0;
                }
                // operator_status = 1;
                if (add_sub_status == 1 || mul_div_bracket_status == 1)
                {
                    temp = 1;
                    temp_string = to_string(sign * temp);
                    postfix.push(temp_string);
                    add_sub_status = 0;
                    mul_div_bracket_status = 0;
                }
                add_sub_status = 0;
                mul_div_bracket_status = 1;
                sign = 1;
                s.push('*');
                s.push(input[i]);
                if (i != input.length())
                {
                    temp = 0;
                }
            }
            else if (s.empty() || precedence(input[i]) > precedence(s.top()))
            {
                decimal = 0; // this block write as a function
                // decimal_status = 0;
                if (num_status == 1)
                {
                    temp_string = to_string(sign * temp);
                    postfix.push(temp_string);
                    num_status = 0;
                }
                else if (input[i] == '+' || input[i] == '-')
                {
                    temp = 0;
                    temp_string = to_string(temp);
                    postfix.push(temp_string);
                    s.push(input[i]);
                }
                sign = 1;
                /*if (num_status == 0 && mul_div_bracket_status == 0)
                {
                    cout << "Wrong input" << endl;
                    exit(1);
                }*/
                if (add_sub_status == 1)
                {
                    cout << "Wrong input" << endl;
                    exit_status = 1;
                }
                else if (mul_div_bracket_status == 1 && (input[i] == '+' || input[i] == '-'))
                {
                    if (input[i] == '-')
                    {
                        sign = -1;
                    }
                    add_sub_status = 1;
                    mul_div_bracket_status = 0;
                }
                else if (mul_div_bracket_status == 0)
                {
                    if (input[i] == '+' || input[i] == '-')
                    {
                        add_sub_status = 1;
                        mul_div_bracket_status = 0;
                    }
                    else if (input[i] == '/' || input[i] == '*')
                    {
                        add_sub_status = 0;
                        mul_div_bracket_status = 1;
                    }
                    s.push(input[i]);
                }
                else
                {
                    cout << "Wrong input" << endl;
                    exit_status = 1;
                }
                /*if (operator_status == 0)
                {
                    s.push(input[i]);
                    operator_status = 1;
                }
                else
                {
                    cout << "Wrong input" << endl;
                    exit(1);
                }*/
                if (exit_status == 0)
                {
                    if (i != input.length() && input != "+" && input != "-")
                    {
                        temp = 0;
                    }
                    else if (input == "+" || input == "-")
                    {
                        temp = 1;
                    }
                }
            }
            else
            {
                decimal = 0;
                // decimal_status = 0;
                if (num_status == 1)
                {
                    temp_string = to_string(sign * temp);
                    postfix.push(temp_string);
                    num_status = 0;
                }
                sign = 1;
                while (!s.empty() && precedence(input[i]) < precedence(s.top()))
                {
                    operator_string[0] = s.top();
                    operator_string[1] = '\0';
                    postfix.push(operator_string);
                    s.pop();
                }
                if (add_sub_status == 0 && mul_div_bracket_status == 0)
                {
                    s.push(input[i]);
                    if (input[i] == '+' || input[i] == '-')
                    {
                        add_sub_status = 1;
                    }
                    else if (input[i] == '/' || input[i] == '*')
                    {
                        mul_div_bracket_status = 1;
                    }
                }
                else
                {
                    cout << "Wrong input" << endl;
                    exit_status = 1;
                    exit(1);
                }
                if (exit_status == 0 && i != input.length() && input != "+" && input != "-")
                {
                    temp = 0;
                }
            }
            /*if (decimal_status == 1) // as number is a string and not a char if this condition is not there then even when number is not completed, decimal will get zero.
            {
                decimal = 0;
            }*/
        }
    }
    /*if (input == "+")
    {
        temp = 1;
    }
    if (input == "-")
    {
        temp = -1;
    }*/
    if (num_status == 1)
    {
        temp_string = to_string(temp);
        postfix.push(temp_string);
    }
    else if (input == "+" || input == "-")
    {
        temp_string = to_string(temp);
        postfix.push(temp_string);
    }
    else if (num_status == 0 && input[i - 1] != ')')
    {
        cout << "Wrong input" << endl;
        exit_status = 1;
    }
    if (exit_status == 0)
    {
        if (s.empty())
        {
            temp = 0;
            temp_string = to_string(temp);
            postfix.push(temp_string);
            s.push('+');
        }
        while (!s.empty() && exit_status == 0)
        {
            if (s.top() == '(' || s.top() == '{' || s.top() == '[')
            {
                cout << "Wrong input" << endl;
                exit_status = 1;
            }
            else
            {
                operator_string[0] = s.top();
                operator_string[1] = '\0';
                postfix.push(operator_string);
                s.pop();
            }
        }
        if (exit_status == 0)
        {
            t = ans(postfix);
        }
    }
    return t;
}

double ans(queue<string> postfix)
{
    stack<string> stack_postfix;
    string operand_1_str;
    string operand_2_str;
    string operator_symbol;
    string front;
    double operand_1;
    double operand_2;
    double result = 0;
    string result_str;
    while (!postfix.empty())
    {
        front = postfix.front();
        if (is_operator(front[0]) == 0 || (front[0] == '-' && is_operator(front[1]) == 0))
        {
            stack_postfix.push(front);
        }
        else
        {
            if (!stack_postfix.empty())
            {
                operand_1_str = stack_postfix.top();
                operand_1 = stod(operand_1_str);
                stack_postfix.pop();
            }
            if (!stack_postfix.empty())
            {
                operand_2_str = stack_postfix.top();
                operand_2 = stod(operand_2_str);
                stack_postfix.pop();
            }
            operator_symbol = front;
            result = calculation(operand_1, operand_2, operator_symbol);
            result_str = to_string(result);
            stack_postfix.push(result_str);
        }
        postfix.pop();
    }
    return result;
}

double calculation(double operand_1, double operand_2, string str)
{
    double ans;
    if (str[0] == '+')
    {
        ans = operand_1 + operand_2;
    }
    else if (str[0] == '-')
    {
        ans = operand_2 - operand_1;
    }
    else if (str[0] == '*')
    {
        ans = operand_1 * operand_2;
    }
    else
    {
        ans = operand_2 / operand_1;
    }
    return ans;
}
