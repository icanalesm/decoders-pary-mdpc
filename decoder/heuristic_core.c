/*
 * File:   heuristic_core.c
 * Author: Canales-Martinez, Isaac Andres
 */

#include <stdlib.h>
#include <math.h>

#include "../fqla/fqla.h"
#include "fqla_util.h"
#include "heuristic_core.h"

static int64_t cq16;     /* ceil(q/6) */
static int64_t fq16;     /* floor(q/6) */
static int64_t cq12;     /* ceil(q/2) */
static int64_t fq12;     /* floor(q/2) */
static int64_t fq56;     /* floor(5q/6) */
static int64_t cq118;    /* ceil(q/18) */
static int64_t fq518;    /* floor(5q/18) */
static int64_t *v01;     /* Auxiliar vector for decoding */

/* Update decision rule of the decoding algorithm */
static void decide_update(int64_t *r1, int64_t *r2, const int64_t *p, size_t k,
                          int64_t t, int64_t q, int64_t q0)
{
	int64_t cq16t, fq16t, cq12t, fq12t, fq56t, cq118t, fq518t, pi;
	size_t i;

	cq16t = cq16 + t;
	fq16t = fq16 - t;
	cq12t = cq12 + t;
	fq12t = fq12 - t;
	fq56t = fq56 - t;
	cq118t = cq118 + t;
	fq518t = fq518 - t;

	for (i = 0; i < k; i++) {
		if ((cq16t <= p[i]) && (p[i] <= fq12t))
			r1[i] = (r1[i] + 1) % q;
		else if ((cq12t <= p[i]) && (p[i] <= fq56t))
			r1[i] = (r1[i] + q - 1) % q;
		pi = p[i] % q0;
		if ((cq118t <= pi) && (pi <= fq16t))
			r2[i] = (r2[i] + 1) % q;
		else if ((cq16t <= pi) && (pi <= fq518t))
			r2[i] = (r2[i] + q - 1) % q;
	}
}

/**
 * mindif()
 *
 * Let t be a number and A be a length-n array of numbers. Compute
 *
 *     min(abs(t - a_1), ... , abs(t - a_n)),
 *
 * where a_i are entries from in A. The array A must be sorted in ascending
 * order.
 *
 * @t:      value to compute the minimum difference
 * @A:      pointer to the array of numbers
 * @len:    length of A
 *
 * Return:
 *   The mimimum absolute value of the difference of t and the entries of A. If
 *   A has length zero, return t.
 *
 * Notes:
 *   It is assumed that A is not a null pointer.
 */
static int64_t mindif(int64_t t, const int64_t *A, size_t len)
{
	int64_t d1, d2;
	size_t i, j, m;

	if (len == 0)
		return t;

	/* Binary search */
	i = 0;
	j = len;
	m = 0;
	while (i < j) {
		m = (i + j) / 2;
		/* Check whether t == A[m] */
		if (t == A[m])
			return 0;
		/* If t < A[m], search on the left */
		if (t < A[m]) {
			/* If t > A[m-1], return min(A[m] - t , t - A[m-1]) */
			if (m > 0 && t > A[m - 1]) {
				d1 = t - A[m - 1];
				d2 = A[m] - t;
				return (d1 >= d2) ? d2 : d1;
			}
			/* Search on left half */
			j = m;
		}
		/* If t > A[m], search on the right */
		else {
			/* If t < A[m+1], return min(A[m], A[m+1]) */
			if (m < len - 1 && t < A[m + 1]) {
				d1 = t - A[m];
				d2 = A[m + 1] - t;
				return (d1 >= d2) ? d2 : d1;
			}
			/* Search on right half */
			i = m + 1;
		}
	}

	return (t <= A[m]) ? A[m] - t : t - A[m];
}

/**
 * mindif_vec()
 *
 * Let t be a lentgh-m array of numbers and A be a length-n array of numbers.
 * Compute
 *
 *     min(abs(t_1 - a_1), ... , abs(t_1 - a_n),
 *                         ...
 *         abs(t_m - a_1), ... , abs(t_m - a_n)),
 *
 * where t_i are entries from t and a_j are entries from in A. The array A must
 * be sorted in ascending order.
 *
 * @t:       pointer to the array of values
 * @len      length of t
 * @A:       pointer to the array of numbers
 * @lenA:    length of A
 *
 * Return:
 *   The mimimum absolute value of the difference of the entries of t and the
 *   entries of A. If A has length zero, return t.
 *
 * Notes:
 *   It is assumed that t and A are not a null pointers.
 */
static int64_t mindif_vec(const int64_t *t, size_t len, const int64_t *A,
                          size_t lenA)
{
	int64_t d, di;
	size_t i;

	d = A[lenA - 1];
	for (i = 0; i < len; i++) {
		di = mindif(t[i], A, lenA);
		if (di < d)
			d = di;
	}

	return d;
}

int decode(int64_t *r1, int64_t *r2, const int64_t *s, const int64_t *h0,
           const int64_t *h1, size_t k, size_t iter, int64_t delta, int64_t q,
           int64_t q0, const int64_t *P, size_t nP)
{
	int64_t t, d;
	size_t i, j;
#if defined (HEURISTIC_H1) || defined (HEURISTIC_H3)
	int64_t q18;
	double tmp, tmp2;

	tmp = ((double) q) / 18;
	q18 = (modf(tmp, &tmp2) <= 0.5) ? ((int64_t) floor(tmp))
	                                : ((int64_t) ceil(tmp));
#endif

	d = delta;
#if defined (HEURISTIC_H3)
	for (; d >= 0; d--) {
#endif
		/* Initialisation */
		for (i = 0; i < k; i++) {
			r1[i] = 0;
			r2[i] = 0;
			v01[i] = s[i];
		}

		for (i = 0; i < iter; i++) {

			/* Compute threshold */
#if defined (HEURISTIC_H1) || defined (HEURISTIC_H3)
			t = q18 - mindif_vec(v01, k, P, nP) - d;
			t = (t < 0) ? 0 : t;
#elif defined (HEURISTIC_H2)
			t = mindif_vec(v01, k, P, nP) + d;
#endif

			/* Decide and update computed error */
			decide_update(r1, r2, v01, k, t, q, q0);

			/* Transform */
			for (j = 0; j < k; j++) {
				if (r1[j] == 2)
					r1[j] = q - 1;
				else if (r1[j] == q - 2)
					r1[j] = 1;
				if (r2[j] == 2)
					r2[j] = q - 1;
				else if (r2[j] == q - 2)
					r2[j] = 1;
			}

			mfq_smul_vfq(v01, h0, h1, r1, r2, k, q);
			vfq_sub(v01, s, v01, k, q);

			if (vfq_iszero(v01, k))
				return 1;
		}
#if defined (HEURISTIC_H3)
	}
#endif

	return 0;
}

int decoder_init(int64_t q, size_t k)
{
	double aux;

	if (!(v01 = (int64_t *) malloc(k * sizeof(int64_t))))
		return -1;

	aux = ((double) q) / 6;
	cq16 = (int64_t) ceil(aux);
	fq16 = (int64_t) floor(aux);
	aux = ((double) q) / 2;
	cq12 = (int64_t) ceil(aux);
	fq12 = (int64_t) floor(aux);
	fq56 = (int64_t) floor(((double) 5 * q) / 6);
	cq118 = (int64_t) ceil(((double) q) / 18);
	fq518 = (int64_t) floor(((double) 5 * q) / 18);

	return 0;
}

void decoder_clean()
{
	free(v01);
}
