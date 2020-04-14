/*
 * Tema 2 ASC
 * 2020 Spring
 */
#include "utils.h"
#include "cblas.h"
#include <string.h>

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

double *my_solver(int N, double *A, double *B) {
	double *first_eq, *second_eq, *res;
	double *A_sq;

	first_eq  = (double *) malloc(N * N * sizeof(*first_eq));
	second_eq = (double *) malloc(N * N * sizeof(*second_eq));
	A_sq 	  = (double *) malloc(N * N * sizeof(*A_sq));

	/* Set the 'B' operand of every
	 * matrix multiplication accordingly
	 */
	memcpy(A_sq, A, N * N * sizeof(*A));
	memcpy(second_eq, B, N * N * sizeof(*B));
	memcpy(first_eq, B, N * N * sizeof(*B));

	/* Compute A squared */
	cblas_dtrmm(CblasRowMajor, CblasLeft, CblasUpper,
			CblasNoTrans,CblasNonUnit, N, N, 1.0, A, N, A_sq, N);
	/* Compute second equation */
	cblas_dtrmm(CblasRowMajor, CblasLeft, CblasUpper,
			CblasNoTrans, CblasNonUnit, N, N, 1.0, A_sq, N, second_eq, N);
	/* Compute first equation */
	cblas_dtrmm(CblasRowMajor, CblasRight, CblasUpper,
			CblasTrans, CblasNonUnit, N, N, 1.0, A, N, first_eq, N);

	/* Add for final result */
	res = matrix_add(first_eq, second_eq, N);

	free(first_eq);
	free(second_eq);
	free(A_sq);

	return res;
}
