# matrix_multiplications_version1
This program calculates the product of two different matrices using N threads.

The matrix's result dimesion is 'm'rows 'n' columns.

The matrix result will be devided into a N sub-matrices of dimensions approximately 'm/N' rows 'n' columns.

Each thread calculate the sub matrix according to his id.
