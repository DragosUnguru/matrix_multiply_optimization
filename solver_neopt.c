/*
 * Tema 2 ASC
 * 2020 Spring
 */
#include "utils.h"

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

double* upper_multiply(double *A, double* B, int N) {
	int i, j, k;
	double *res;

	res = calloc(N * N, sizeof(*res));

	for (i = 0; i < N; i++) {
		for (j = i; j < N; j++) {

			for (k = 0; k <= j; k++)
				res[i * N + j] += A[i * N + k] * B[k * N + j];
		}
	}

    return res;
}

double* simple_multiply(double *A, double* B, int N) {
	int i, j, k;
	double *res;

	res = malloc(N * N * sizeof(*res));

	for (i = 0; i < N; i++) {
		for (j = 0; j < N; j++) {
			res[i * N + j] = 0;

			for (k = 0; k < N; k++)
				res[i * N + j] += A[i * N + k] * B[k * N + j];
		}
	}

    return res;
}

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

	A_squared = upper_multiply(A, A, N);
	second = simple_multiply(A_squared, B, N);
	transpose(A, N);
	first = simple_multiply(B, A, N);
	res = matrix_add(first, second, N);

	free(A_squared);
	free(first);
	free(second);
	
	return res;
}
