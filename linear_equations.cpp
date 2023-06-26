#include <iostream>
#include <vector>
#include "linear_equations.h"
using namespace std;

#define SIZE 26

int main(void)
{
    int no_of_equations, no_of_variables;
    cout << "Enter no of equations : ";
    cin >> no_of_equations;
    cout << "Enter no of variables : ";
    cin >> no_of_variables;
    double arr[no_of_equations][no_of_variables + 1];
    int no_of_pivots;
    if (no_of_equations <= no_of_variables)
    {
        arr_initializer(*arr, no_of_equations, no_of_variables);
        int i, j;
        row_echelon_form(*arr, no_of_equations, no_of_variables, 0);
        no_of_pivots = pivots(*arr, no_of_equations, no_of_variables);
        if (no_of_pivots == no_of_variables)
        {
            row_reduced_echelon_form(*arr, no_of_equations, no_of_variables, 1);
            for (i = 0; i < no_of_equations; i++)
            {
                for (j = 0; j < no_of_variables + 1; j++)
                {
                    cout.precision(2);
                    cout << fixed << arr[i][j] << " ";
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

    return 0;
}

void arr_initializer(double *arr, int no_of_equations, int no_of_varaibles)
{
    int i, j;
    for (i = 0; i < no_of_equations; i++)
    {
        for (j = 0; j < no_of_varaibles + 1; j++)
        {
            cin >> *(arr + i * (no_of_varaibles + 1) + j);
        }
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

void input()
{
    string input = "";
    string quit = "quit";
    string inputs[26];
    int i = 0;
    int variables_status[26] = {0};
    int no_of_equations = 0;
    int no_of_variables;
    cin >> input;
    int start;
    int *arr = &start;
    while (input != "quit")
    {
        cin >> inputs[i];
        i++;
    }
}

void filling_array(string &input, int *variables_status, int equation_no, int *arr, vector<vector<int>> &matrix)
{
    int i;
    int length = input.length();
    int variables_poisiton[26] = {-1};
    int j = 65;
    int temp = 0;
    int no_of_variables = 0;

    for (i = 0; i < length; i++)
    {
        if (input[i] >= 48 && input[i] <= 57)
        {
            temp = temp * 10 + int(input[i]);
        }
        else if (input[i] >= 65 && input[i] <= 90)
        {
            variables_status[input[i] - 65] = 1;
            if (variables_poisiton[i] == -1)
            {
                variables_poisiton[i] = no_of_variables;
                no_of_variables = no_of_variables + 1;
            }
            matrix[equation_no][no_of_variables] = temp;
            temp = 0;
        }
    }
}