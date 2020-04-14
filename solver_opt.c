/*
 * Tema 2 ASC
 * 2020 Spring
 */
#include "utils.h"

/* Transposes "matrix" of size N */
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

/* Proprietary function for computing A
 * squared where A is an upper triangular
 * matrix
 */
double* upper_multiply(double *A, double* B, int N) {
	register double tmp;
	register int i, j, k;
	register double *res;
	register double *prodA;
	register double *prodB;

	res = malloc(N * N * sizeof(*res));

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

/* Multiplies matrices A and B of size N
 * "is_upper" signals if A is upper-triangular
 * returns the result as a newly allocated double*
 */
double* matrix_multiply(double *A, double* B, int N, char is_upper) {
	register int i, j, k;
	register double *res;
	register double *prodA;
	register double *prodB;
    register double *ptrRes;

	res = malloc(N * N * sizeof(*res));

    prodA = A;
	for (i = 0; i < N; ++i) {
        prodA = is_upper ? prodA + i : prodA;
        prodB = is_upper ? B + i * N : B;

		for (k = is_upper ? i : 0; k < N; ++k) {
            ptrRes = res + i * N;

			for (j = 0; j < N; ++j) {
				*ptrRes += *prodA * *prodB;
                ++ptrRes;
                ++prodB;
			}
            ++prodA;
		}
	}

	return res;
}

/* Multiplies matrices A and B of size N
 * knowing that B is lower triangular
 * returns the result as a newly allocated double*
 */
double* matrix_multiply_lw(double *A, double* B, int N) {
	register int i, j, k;
	register double *res;
	register double *prodA;
	register double *prodB;
    register double *ptrRes;

	res = malloc(N * N * sizeof(*res));

    prodA = A;
	for (i = 0; i < N; ++i) {
        prodA = prodA;
        prodB = B;

		for (k = 0; k < N; ++k) {
			prodB = B + k * N;
            ptrRes = res + i * N;

			for (j = 0; j <= k; ++j) {
				*ptrRes += *prodA * *prodB;
                ++ptrRes;
                ++prodB;
			}
            ++prodA;
		}
	}

	return res;
}

/* Adds A and B of size N.
 * Returns a newly allocated double*
 * containing the result
 */
double* matrix_add(double* A, double* B, int N) {
	register int i, j;
	register double *res;
	register double *to;
	register double *fromA, *fromB;

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
	second = matrix_multiply(A_squared, B, N, 1);

	transpose(A, N);

	first = matrix_multiply_lw(B, A, N);
	res = matrix_add(first, second, N);

	/* Free */
	free(A_squared);
	free(first);
	free(second);
	
	return res;
}
