/*
 * Tema 2 ASC
 * 2020 Spring
 */
#include "utils.h"
extern double ddot_(int ceva, double* v, int altceva, double* u, int plm);

/* 
 * Add your BLAS implementation here
 */

double* matrix_multiply(int N, double *A, double *B) {
	double *rowA, *colB;
	double *res;
	int i;

	res = (double *) malloc(N * sizeof(*res));

	rowA = A;
	colB = B;
	for (i = 0; i < N; ++i) {
		res[i] = ddot_(N, rowA, 1, colB, N);

		rowA += N;
		colB++;
	}

	return res;
}

double* my_solver(int N, double *A, double *B) {
	double *res;

	res = matrix_multiply(N, A, B);

	return res;
}
