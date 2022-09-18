/* ADT Matrix */
//
#ifndef _MATRIX_H
#define _MATRIX_H

typedef struct Matrix {
	unsigned int nlins;
	unsigned int ncols;
	double      *values;
} Matrix;
#define VALUES(m, i, j) (m.values[i * m.ncols + j])
extern Matrix matrix_nul;

Matrix matrix_zeros(unsigned int nlins, unsigned int ncols);
Matrix matrix_ones(unsigned int nlins, unsigned int ncols);
Matrix matrix_identity(unsigned int nlins, unsigned int ncols);
Matrix matrix_copy(Matrix m);
Matrix matrix_apply(double (*f)(double val), Matrix m);
void matrix_free(Matrix *m);
double       matrix_value(Matrix m, int i, int j);
unsigned int matrix_nlins(Matrix m);
unsigned int matrix_ncols(Matrix m);

// Métodos criados pelo aluno: Daniel Santiago da Silva
Matrix matrix_create(); // Done
Matrix matrix_scalar_mul(double n, Matrix m); // Done
Matrix matrix_scalar_sum(double n, Matrix m); // Done
Matrix matrix_scalar_dif(double n, Matrix m); // Done
Matrix matrix_mul(Matrix A, Matrix B); // Done
Matrix matrix_sum(Matrix A, Matrix B); // Done
Matrix matrix_dif(Matrix A, Matrix B); // Done
int    matrix_compare(Matrix A, Matrix B); // Done
double matrix_det(Matrix m); // Done
Matrix matrix_transpose(Matrix m); // Done
Matrix matrix_get_cofactor(Matrix m, int i, int j); // Done
Matrix matrix_inverse(Matrix m); // Done
void   print_matrix(const char *const name, const Matrix m); // Done

#endif
