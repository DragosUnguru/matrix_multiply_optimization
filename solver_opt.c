/*
 * Tema 2 ASC
 * 2020 Spring
 */
#include "utils.h"

void transpose(double *matrix, int N) {
	register int a, b;
	register double *from;
	register double *to;

	for (a = 1; a < N; ++a) {
		to = matrix + a * N;
		from = matrix + a;

		for (b = 0; b < a; ++b) {
			*to = *from;
			*from = 0;

			from += N;
			to++;
		}
	}
}

double* upper_multiply(double *A, double* B, int N) {
	register double tmp;
	register int i, j, k;
	register double *res;
	register double *prodA;
	register double *prodB;

	res = calloc(N * N, sizeof(*res));

	for (i = 0; i < N; ++i) {
		for (j = i; j < N; ++j) {
			prodA = A + i * N;
			prodB = B + j;
			tmp = 0;

			for (k = 0; k <= j; ++k) {
				tmp += *prodA * *prodB;
				++prodA;
				prodB += N;
			}
			res[i * N + j] = tmp;
		}
	}

	return res;
}

double* simple_multiply(double *A, double* B, int N) {
	register double tmp;
	register int i, j, k;
	register double *res;
	register double *prodA;
	register double *prodB;

	res = malloc(N * N * sizeof(*res));

	for (i = 0; i < N; ++i) {
		for (j = 0; j < N; ++j) {
			prodA = A + i * N;
			prodB = B + j;
			tmp = 0;

			for (k = 0; k < N; ++k) {
				tmp += *prodA * *prodB;
				++prodA;
				prodB += N;
			}
			res[i * N + j] = tmp;
		}
	}

	return res;
}

double* matrix_add(double* A, double* B, int N) {
	register int i, j;
	double *res;
	double *to;
	double *fromA, *fromB;

	res = malloc(N * N * sizeof(*res));

	for (i = 0; i < N; ++i) {
		to = res + i * N;
		fromA = A + i * N;
		fromB = B + i * N;

		for (j = 0; j < N; ++j) {
			*to = *fromA + *fromB;
			++to;
			++fromA;
			++fromB;
		}
	}
	return res;
}

double* my_solver(int N, double *A, double* B) {
	double* A_squared;
	double* first;
	double* second;
	double* res;

	/* Compute formula */
	A_squared = upper_multiply(A, A, N);
	second = simple_multiply(A_squared, B, N);

	transpose(A, N);

	first = simple_multiply(B, A, N);
	res = matrix_add(first, second, N);

	/* Free */
	free(A_squared);
	free(first);
	free(second);
	
	return res;
}
