# matrix-calculator

***a program that does basic math operation on two matrices of dimensions up to 10×10***

This is a program that asks the user for two matrices up to size of 10×10, then can do a number of basic operations on them.  
These operations are:  
***A+B, A-B, B-A, A×B, B×A, A/B, B/A, |A|, |B|***  

## How The Functions Work

### **multiply**

#### Function for printing a product of two matrices

Multiplication takes place as follows:  
In the resultant matrix R, the element Rij is the sum of products of the elements of row i in matrix A and column j in matrix B.  

``` c++
( 1 2 )   ( 1 2 3 )   ( 1 × 1 + 2 × 4    1 × 2 + 2 × 5    1 × 3 + 2 × 6 )   ( 9  12 15 )  
( 3 4 ) × (       ) = ( 3 × 1 + 4 × 4    3 × 2 + 4 × 5    3 × 3 + 4 × 6 ) = ( 19 26 33 )  
( 5 6 )   ( 4 5 6 )   ( 5 × 1 + 6 × 4    5 × 2 + 6 × 5    5 × 3 + 6 × 6 )   ( 29 40 51 )
```

### **multiplyDouble**

#### Function for printing a product of two matrices, where the second matrix contains decimal numbers

This function operates the same as the above, with the only difference is that it is mainly needed for division, as the inverse of a matrix may contain decimals. That is why the second matrix is declared as a double.

### **det**

#### Function for calculating the determinant of a matrix

The following determinant method is called Laplace expansion.  
*note that recursion was used in this function*  
If the matrix is 2×2, calculate just like that:  

``` c++
| 2 7 |  = 2 × 6 - 7 × 5  
| 5 6 |  = -23  
```

If the matrix is more than 2×2, eg 3×3, calculate determinant as such:  

``` c++
| 2 6 7 |       |  2 4  |       |  8 4  |       |  8 2  |     2 × (2 × 1 - 4 × 9)  
| 8 2 4 | = 2 × |       | - 6 × |       | + 7 × |       | = - 6 × (8 × 1 - 4 × 6) = 448  
| 6 9 1 |       |  9 1  |       |  6 1  |       |  6 9  |   + 7 × (8 × 9 - 6 × 2)
```

### **divide**

#### Function for printing quotient of two matrices

In division, we multiply the divident by the inverse of the divisor.  
The divisor must be a square matrix with a determinant that is a non-zero value.  
Otherwise, it would not have an inverse matrix.  
The following method is called the inverse matrix method, where we get the matrix of minors, cofactors, and adjugates (adjoints).  
It bears a similarity to the Laplace expansion that we used in the determinant.  
Also, the number of columns of the divident must be equal to the dimensions of the divisor  
***In case of 2×2:***  

``` c++
( a b ) ^ -1   (  d -b )  
(     )      = (       )  
( c d )        ( -c  a )  
```

***In case of 3×3:***  
We get the matrix of minors, get the result's matrix of cofactors, and then get the adjoint by transposing the result. Finally, divide the adjoint by the determinant of the original matrix.  
The following matrix has a determinant of -6  

``` c++
                  (   |3 5|  |4 5|  |4 3|   )  
                  (   |4 0| -|1 0|  |1 4|   )  
                  (                         )  
( 2 -1 3 ) ^ -1   (  |-1 3|  |2 3|  |2 -1|  )   ( -20  5 13 )       ( -20 12 -14 )  
( 4  3 5 )      = ( -| 4 0|  |1 0| -|1  4|  ) = (  12 -3 -9 ) ----> (   5 -3   2 ) / -6  
( 1  4 0 )        (                         )   ( -14  2 10 )       (  13 -9  10 )  
                  (  |-1 3|  |2 3|  |2 -1|  )  
                  (  | 3 5| -|4 5|  |4  3|  )  
```

then we multiply the divident by the inverse of the divisor as illustrated above.
