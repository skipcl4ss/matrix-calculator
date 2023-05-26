#include <iostream>
#include <cmath>
#include "operations.h"
using namespace std;
// Multiplication takes place as follows
// | 1 2 |   | 1 2 3 |   | 1 * 1 + 2 * 4    1 * 2 + 2 * 5    1 * 3 + 2 * 6) |   | 9  12 15 |
// | 3 4 | * |       | = | 3 * 1 + 4 * 4    3 * 2 + 4 * 5    3 * 3 + 4 * 6) | = | 19 26 33 |
// | 5 6 |   | 4 5 6 |   | 5 * 1 + 6 * 4    5 * 2 + 6 * 5    5 * 3 + 6 * 6) |   | 29 40 51 |
void multiply(int matrix1[10][10], int matrix2[10][10], int row1, int common, int col2)
{
    int sumOfProducts = 0;
    // Iterate through each row in the 1st matrix
    for (int i = 0; i < row1; i++)
    {
        // Iterate through each column in the 2nd matrix
        for (int k = 0; k < col2; k++)
        {
            // Iterate through each element in the row and in the column in the 1st and 2nd matrices respectively
            // Since we iterate through both by using the same loop, each two elements will be corresponding
            for (int j = 0; j < common; j++)
            {
                // Multiply each two corresponding elements and add it to the sum of products
                sumOfProducts += matrix1[i][j] * matrix2[j][k];
            }
            // Print each element in the shape of the product matrix, which will be common * common
            // Also approximating to the nearest integer
            cout << round(sumOfProducts) << " ";
            sumOfProducts = 0;
        }
        cout << endl;
    }
}
// Same as above, only with the second matrix as double
void multiplyDouble(int matrix1[10][10], double matrix2[10][10], int row1, int common, int col2)
{
    double sumOfProducts = 0;
    for (int i = 0; i < row1; i++)
    {
        for (int k = 0; k < col2; k++)
        {
            for (int j = 0; j < common; j++)
            {
                sumOfProducts += matrix1[i][j] * matrix2[j][k];
            }
            // Approximation to the nearest integer using llround to return long long in case of large values
            cout << llround(sumOfProducts) << " ";
            sumOfProducts = 0;
        }
        cout << endl;
    }
}
// The following determinant method is called Laplace expansion
// If the matrix is 2*2, calculate just like that:
// | 2 7 |     = 2 * 6 - 7 * 5
// | 5 6 |     = -23
// If the matrix is more than 2*2, eg 3*3, calculate determinant as such:
// | 2 6 7 |       |  2 4  |       |  8 4  |       |  8 2  |     2 * (2 * 1 - 4 * 9)
// | 8 2 4 | = 2 * |       | - 6 * |       | + 7 * |       | = - 6 * (8 * 1 - 4 * 6) = 448
// | 6 9 1 |       |  9 1  |       |  6 1  |       |  6 9  |   + 7 * (8 * 9 - 6 * 2)
long long det(int matrix[10][10], int n)
{
    if (n == 1)
    {
        return matrix[0][0];
    }

    if (n == 2)
    {
        return (matrix[0][0] * matrix[1][1] - matrix[0][1] * matrix[1][0]);
    }
    // Determinant value is saved in determinant, mat is the smaller matrix
    long long determinant = 0;
    int mat[10][10];
    // Iterate through the elements in the first row
    for (int i = 0; i < n; i++)
    {
        // Save the smaller matrix elements in mat
        // j starts from 1 as no element from the 1st row will be saved
        // colk is the index of mat, it is necessary as k increases as the continue case iterated
        // That is not the case for j since it always starts with 1 and is always shifted by 1 in mat
        for (int j = 1; j < n; j++)
        {
            for (int k = 0, colk = 0; k < n; k++)
            {
                // Condition to ignore the cases where the element is in the same column of element matrix[0][i]
                if (i == k)
                {
                    continue;
                }
                // Save the valid element in its proper place in mat, colk++ is not at the top of the loop the solve the continue issue
                mat[j - 1][colk] = matrix[j][k];
                colk++;
            }
        }
        // Calculate the determinant, pow(-1, i) is to alternate between 1 and -1, matrix[0][i] is the element in the first row, det(mat, n - 1) is the determinant of the smaller matrix
        determinant += ((int)pow(-1, i)) * matrix[0][i] * det(mat, n - 1);
    }
    return determinant;
}
// In division, we multiply the divident by the inverse of the divisor
// The divisor must be a square matrix with a determinant that is a non-zero value
// Otherwise, it would not have an inverse matrix
// The following method is called the inverse matrix method, where wee use minors, cofactors, and adjugates
// It bears a similarity to the Laplace expansion that we used in the determinant
// Also, the number of columns of the divident must be equal to the dimensions of the divisor
// In case of 2*2
// | a b | ^ -1   |  d -b |
// |     |      = |       |
// | c d |        | -c  a |
// In case of 3*3, we get the cofactor of the matrix, transpose it, and divide it by the determinant of the matrix
// The following matrix has a determinant of -6
//                   |   |3 5|  |4 5|  |4 3|   |
//                   |   |4 0| -|1 0|  |1 4|   |
//                   |                         |
// | 2 -1 3 | ^ -1   |  |-1 3|  |2 3|  |2 -1|  |   | -20  5 13 |       | -20 12 -14 |
// | 4  3 5 |      = | -| 4 0|  |1 0| -|1  4|  | = |  12 -3 -9 | ----> |   5 -3   2 | / -6
// | 1  4 0 |        |                         |   | -14  2 10 |       |  13 -9  10 |
//                   |  |-1 3|  |2 3|  |2 -1|  |
//                   |  | 3 5| -|4 5|  |4  3|  |
// then we multiply the divident by the inverse of the divisor
void divide(int divident[10][10], int divisor[10][10], int row1, int n)
{
    // inv is the matrix where the inverse is saved, note that it is double
    // mat is the matrix used for inner determinants
    // The value of the divisor's determinant is vaved in determinant
    double inv[10][10];
    int mat[10][10];
    double determinant = det(divisor, n);
    // If the divisor 1*1, divide and print each element in the dividents row by the divisor
    if (n == 1)
    {
        for (int i = 0; i < row1; i++)
        {
            cout << round(divident[i][0] / (float) divisor[0][0]) << endl;
        }
    }
    // Get the inverse of the divisor
    else
    {
        if (n == 2)
        {
            for (int i = 0; i < n; i++)
            {
                for (int j = 0; j < n; j++)
                {
                    // Swap the diagonals and divide by the dereminant
                    if (i == 0 && j == 0)
                    {
                        inv[0][0] = divisor[1][1] / determinant;
                    }
                    else if (i == 1 && j == 1)
                    {
                        inv[1][1] = divisor[0][0] / determinant;
                    }
                    // Multiply the reaining elements by -1 and divide by the determinant
                    else
                    {
                        inv[i][j] = -1 * divisor[i][j] / determinant;
                    }
                }
            }
        }
        else
        {
            // Iterate through each element
            for (int i = 0; i < n; i++)
            {
                for (int j = 0; j < n; j++)
                {
                    // Iterate one more to make the inner determinant matrix
                    // rowk and coll have the same purpose as colk in det() function
                    for (int k = 0, rowk = 0; k < n; k++)
                    {
                        // Check for the validity of the elements
                        if (i == k)
                        {
                            continue;
                        }

                        for (int l = 0, coll = 0; l < n; l++)
                        {
                            // Check for the validity of the elements
                            if (j == l)
                            {
                                continue;
                            }
                            // Save the elements in mat with the corresponding indices
                            mat[rowk][coll] = divisor[k][l];
                            coll++;
                        }
                        rowk++;
                    }
                    // Divide each corresponding determinant by the divisor's determinant
                    // Multiply by -1 if needed
                    inv[j][i] = pow(-1, i + j) * det(mat, n - 1) / determinant;
                }
            }
        }
        // Print the product of the divident and the inverse of the divisor
        multiplyDouble(divident, inv, row1, n, n);
    }
}