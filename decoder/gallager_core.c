/*
 * File:   gallager_core.c
 * Author: Canales-Martinez, Isaac Andres
 */

#include <stdlib.h>
#include <math.h>

#include "../fqla/fqla.h"
#include "fqla_util.h"
#include "gallager_core.h"
#include "gallager_thr.h"

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

int decode(int64_t *r1, int64_t *r2, const int64_t *s, const int64_t *h0,
           const int64_t *h1, size_t k, size_t iter, int64_t q, int64_t q0)
{
	int64_t t;
	size_t i, j;

	/* Initialisation */
	for (i = 0; i < k; i++) {
		r1[i] = 0;
		r2[i] = 0;
		v01[i] = s[i];
	}

	for (i = 0; i < iter; i++) {

		/* Update threshold */
		update_thr(t, iter, i);

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
