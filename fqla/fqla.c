/*
 * File:   fqla.c
 * Author: Canales-Martinez, Isaac Andres
 */

#include <inttypes.h>

#include "fqla.h"

void vfq_add(int64_t *dest, const int64_t *a, const int64_t *b, size_t len,
             int64_t q)
{
	size_t i;

	for (i = 0; i < len; i++)
		dest[i] = (a[i] + b[i]) % q;
}

void vfq_sub(int64_t *dest, const int64_t *a, const int64_t *b, size_t len,
             int64_t q)
{
	size_t i;

	for (i = 0; i < len; i++)
		dest[i] = (a[i] - b[i] + q) % q;
}

int vfq_iseq(const int64_t *a, const int64_t *b, size_t len)
{
	size_t i;

	for (i = 0; i < len; i++) {
		if (a[i] != b[i])
			return 0;
	}

	return 1;
}

int vfq_iszero(const int64_t *a, size_t len)
{
	size_t i;

	for (i = 0; i < len; i++) {
		if (a[i] != 0)
			return 0;
	}

	return 1;
}

void vfq_fprint(FILE *stream, const int64_t *a, size_t len)
{
	size_t i;

	if (len == 0) {
		fprintf(stream, "[]");
		return;
	}

	fprintf(stream, "[");
	for (i = 0; i < len - 1; i++)
		fprintf(stream, "%"PRIi64", ", a[i]);
	fprintf(stream, "%"PRIi64"]", a[i]);
}
