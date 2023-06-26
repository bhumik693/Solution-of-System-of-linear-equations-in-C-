#include <iostream>
#include <stack>
#include <queue>
#include <string>
#include <math.h>
// #include "infix_postfix.h"
using namespace std;

#define SIZE 26
void zero(double *arr);
void filling_array(string &input, int equation_no, int &no_of_variables, int *variables_poisiton, double *arr, queue<double> &nums_value);
void input_series(double *arr, queue<double> &nums_value);
int is_operator(char input);
int precedence(char input);
double infix_to_postfix(string input);
double ans(queue<string> postfix);
double calculation(double operand_1, double operand_2, string str);

int main()
{
    double arr[SIZE][SIZE];
    queue<double> nums_value;
    input_series(*arr, nums_value);

    cout << arr[0][0] << " " << arr[0][1] << " " << arr[0][2] << endl;
    cout << arr[1][0] << " " << arr[1][1] << " " << arr[1][2] << endl;
    cout << arr[2][0] << " " << arr[2][1] << " " << arr[2][2] << endl;
    return 0;
}

void zero(double *arr)
{
    int i, j;
    for (i = 0; i < SIZE; i++)
    {
        for (j = 0; j < SIZE; j++)
        {
            *(arr + i * SIZE + j) = 0;
        }
    }
}

void input_series(double *arr, queue<double> &nums_value)
{
    string input = "";
    int i;
    int equation_no = 0;
    int no_of_variables = 0;
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
        filling_array(input, equation_no, no_of_variables, variables_poisiton, arr, nums_value);
        equation_no = equation_no + 1;
        getline(cin, input);
    }
    cout << "no_of_variables " << no_of_variables << endl;
    for (i = 0; i < equation_no; i++)
    {
        *(arr + i * (no_of_variables + 1) + no_of_variables) = nums_value.front();
        cout << "front " << nums_value.front() << endl;
        nums_value.pop();
    }
}

void filling_array(string &input, int equation_no, int &no_of_variables, int *variables_poisiton, double *arr, queue<double> &nums_value)
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
            // cout << "bye" << endl;
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
                *(arr + SIZE * equation_no + variables_poisiton[input[i] - 97]) = *(arr + SIZE * equation_no + variables_poisiton[input[i] - 97]) + num;
                // cout << "after " << *(arr + SIZE * equation_no + variables_poisiton[input[i] - 97]) << endl;
            }
            else
            {
                *(arr + SIZE * equation_no + variables_poisiton[input[i] - 97]) = *(arr + SIZE * equation_no + variables_poisiton[input[i] - 97]) - num;
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
    int sign = 1;
    string temp_string;
    char operator_string[2];
    int decimal = 0;
    stack<char> s;
    for (i = 0; i < input.length(); i++)
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
                cout << 1 << endl;
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
                cout << 2 << endl;
                cout << "Wrong input" << endl;
                exit(1);
            }
            else if (input[i] == ')')
            {
                cout << 3 << endl;
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
                while (!s.empty() && s.top() != '(')
                {
                    operator_string[0] = s.top();
                    operator_string[1] = '\0';
                    postfix.push(operator_string);
                    s.pop();
                    if (s.empty())
                    {
                        cout << "Wrong input" << endl;
                        exit(1);
                    }
                }
                if (s.empty())
                {
                    cout << "Wrong input" << endl;
                    exit(1);
                }
                s.pop();
            }
            else if (input[i] == '(')
            {
                cout << 4 << endl;
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
                cout << 3 << endl;
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
                while (!s.empty() && s.top() != '{')
                {
                    operator_string[0] = s.top();
                    operator_string[1] = '\0';
                    postfix.push(operator_string);
                    s.pop();
                    if (s.empty() || operator_string[0] == '(')
                    {
                        cout << "Wrong input" << endl;
                        exit(1);
                    }
                }
                if (s.empty())
                {
                    cout << "Wrong input" << endl;
                    exit(1);
                }
                s.pop();
            }
            else if (input[i] == '{')
            {
                cout << 4 << endl;
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
                cout << 3 << endl;
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
                while (!s.empty() && s.top() != '[')
                {
                    operator_string[0] = s.top();
                    operator_string[1] = '\0';
                    postfix.push(operator_string);
                    s.pop();
                    if (s.empty() || operator_string[0] == '(' || operator_string[0] == '{')
                    {
                        cout << "Wrong input" << endl;
                        exit(1);
                    }
                }
                if (s.empty())
                {
                    cout << "Wrong input" << endl;
                    exit(1);
                }
                s.pop();
            }
            else if (input[i] == '[')
            {
                cout << 4 << endl;
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
                cout << 5 << endl;
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
                    exit(1);
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
                    exit(1);
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
                if (i != input.length() && input != "+" && input != "-")
                {
                    temp = 0;
                }
                else if (input == "+" || input == "-")
                {
                    temp = 1;
                }
            }
            else
            {
                cout << 6 << endl;
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
                    exit(1);
                }
                if (i != input.length() && input != "+" && input != "-")
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
        exit(1);
    }
    if (s.empty())
    {
        temp = 0;
        temp_string = to_string(temp);
        postfix.push(temp_string);
        s.push('+');
    }
    while (!s.empty())
    {
        if (s.top() == '(' || s.top() == '{' || s.top() == '[')
        {
            printf("\n Wrong input\n");
            exit(1);
        }
        operator_string[0] = s.top();
        operator_string[1] = '\0';
        postfix.push(operator_string);
        s.pop();
    }
    double t = ans(postfix);
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
            cout << "result " << result << endl;
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
