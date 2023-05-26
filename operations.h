// Function for printing a product of two matrices
void multiply(int matrix1[10][10], int matrix2[10][10], int row1, int common, int col2);
// Function for printing a product of two matrices, where the second matrix contains decimal numbers
// This function is mainly needed in the division, as the inverse of a matrix may contain decimals
void multiplyDouble(int matrix1[10][10], double matrix2[10][10], int row1, int common, int col2);
// Function for calculating the determinant of a matrix
long long det(int matrix[10][10], int n);
// Function for printing quotient of two matrices
void divide(int divident[10][10], int divisor[10][10], int row1, int n);