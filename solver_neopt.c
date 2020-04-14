/*
 * Tema 2 ASC
 * 2020 Spring
 */
#include "utils.h"

enum MUL_TYPE {Upper, Lower, Normal};

/* Transposes "matrix" of size N */
void transpose(double *matrix, int N) {
	int a, b;
	double tmp;

	/* Swap values on either side of the first diagonal */
	for (a = 1; a < N; a++) {
		for (b = 0; b < a; b++) {
			tmp = matrix[a * N + b];
			matrix[a * N + b] = matrix[b * N + a];
			matrix[b * N + a] = tmp;
		}
	}
}

/* Proprietary function for computing A
 * squared where A is an upper triangular
 * matrix
 */
double* square_upper(double *A, int N) {
	int i, j, k;
	double *res;

	res = calloc(N * N, sizeof(*res));

	for (i = 0; i < N; i++) {
		for (j = i; j < N; j++) {
			for (k = 0; k <= j; k++) {
				res[i * N + j] += A[i * N + k] * A[k * N + j];
			}
		}
	}

	return res;
}

/* Multiplies matrices A and B of size N
 * "is_upper" signals if A is upper-triangular
 * returns the result as a newly allocated double*
 */
double* matrix_multiply(double *A, double* B, int N, char is_upper) {
	int i, j, k;
	double *res;

	res = calloc(N * N, sizeof(*res));

	for (i = 0; i < N; i++) {
		for (j = 0; j < N; j++) {
			res[i * N + j] = 0;

			for (k = is_upper ? i : 0; k < N; k++)
				res[i * N + j] += A[i * N + k] * B[k * N + j];
		}
	}

	return res;
}

/* Adds A and B of size N.
 * Returns a newly allocated double*
 * containing the result
 */
double* matrix_add(double* A, double* B, int N) {
	int i, j;
	double *res;

	res = malloc(N * N * sizeof(*res));

	for (i = 0; i < N; i++) {
		for (j = 0; j < N; j++) {
			res[i * N + j] = A[i * N + j] + B[i * N + j];
		}
	}
	return res;
}

double* my_solver(int N, double *A, double* B) {
	double* A_squared;
	double* first;
	double* second;
	double* res;

	/* Compute second equation */
	A_squared = square_upper(A, N);
	second = matrix_multiply(A_squared, B, N, 1);

	/* Compute first equation */
	transpose(A, N);
	first = matrix_multiply(B, A, N, 0);

	/* Add the two to final result */
	res = matrix_add(first, second, N);

	free(A_squared);
	free(first);
	free(second);

	return res;
}
