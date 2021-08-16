/*
 * File:   fqla_util.c
 * Author: Canales-Martinez, Isaac Andres
 */

#include <stdlib.h>

#include "fqla_util.h"

#define randint(a, b)        ((a) + rand() % ((b) - (a) + 1))

void vfq_ranset(int64_t *dest, size_t len, const int64_t *S, size_t lenS)
{
	size_t i;

	lenS--;
	for (i = 0; i < len; i++)
		dest[i] = S[randint(0, lenS)];
}

void vfq_ranbset(int64_t *dest, size_t len, const int64_t *S, size_t lenS,
                 size_t t)
{
	size_t frq[lenS], i, j;
	int bal;

	t = (len / lenS) - t;

	for (i = 0; i < lenS; i++)
		frq[i] = 0;

	do {
		lenS--;
		for (i = 0; i < len; i++) {
			j = randint(0, lenS);
			dest[i] = S[j];
			frq[j]++;
		}
		lenS++;
		bal = 1;
		for (i = 0; i < lenS; i++) {
			if (frq[i] < t)
				bal = 0;
			frq[i] = 0;
		}
	} while (!bal);
}

void mfq_smul_vfq(int64_t *dest, const int64_t *m0, const int64_t *m1,
                  const int64_t *a0, const int64_t *a1, size_t len, int64_t q)
{
	size_t i, j, k;

	for (i = 0; i < len; i++) {
		dest[i] = 0;
		for (j = 0, k = len - i; j < len; j++, k++) {
			if (k == len)
				k = 0;
			dest[i] += m0[k] * a0[j];
			dest[i] += m1[k] * a1[j];
		}
		dest[i] %= q;
	}
}
