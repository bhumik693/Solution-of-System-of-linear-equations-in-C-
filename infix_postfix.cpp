#include <iostream>
#include <stack>
#include <queue>
#include <string>
#include <math.h>
#include "infix_postfix.h"
using namespace std;

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