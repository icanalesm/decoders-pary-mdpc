/*
 * File:   gallager.c
 * Author: Canales-Martinez, Isaac Andres
 */

#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <time.h>

#include "decoder/fqla_util.h"
#include "decoder/gallager_core.h"
#include "fqla/fqla.h"

static int64_t q, *Id, *h0, *h1, *r1, *r2, *r1d, *r2d, *s;
static size_t k, d, nId, iter, nmtx, imtx;

static void clean();
static void print_usage(const char *cmd);
static int process_args(int argc, char **argv);
static int setup();

static void clean()
{
	free(Id);
	free(h0);
	free(h1);
	free(r1);
	free(r2);
	free(r1d);
	free(r2d);
	free(s);
}

static void print_usage(const char *cmd)
{
	char *aux = strrchr(cmd, '/');

	if (aux)
		cmd = aux + 1;

	fprintf(stdout, "Usage: %s k q iter [nmtx [imtx]]\n", cmd);
}

static int process_args(int argc, char **argv)
{
	char *cmd = *argv;

	if (argc < 4) {
		print_usage(cmd);
		return -1;
	}

	argv++;
	argc--;

	k = strtoll(*(argv++), NULL, 10);
	q = strtoll(*(argv++), NULL, 10);
	iter = strtoll(*(argv++), NULL, 10);
	argc -= 3;

	nmtx = (argc > 0) ? strtoll(*(argv++), NULL, 10) : 1;
	imtx = (argc > 1) ? strtoll(*argv, NULL, 10) : 1;

	return 0;
}

static int setup()
{
	if (!(Id = (int64_t *) malloc(nId * sizeof(int64_t)))) {
		fprintf(stderr, "error: Cannot allocate memory for set I_d\n");
		return -1;
	}
	if (!(h0 = (int64_t *) malloc(k * sizeof(int64_t)))) {
		fprintf(stderr, "error: Cannot allocate memory for vector h0\n");
		goto err_free_Id;
	}
	if (!(h1 = (int64_t *) malloc(k * sizeof(int64_t)))) {
		fprintf(stderr, "error: Cannot allocate memory for vector h1\n");
		goto err_free_h0;
	}
	if (!(r1 = (int64_t *) malloc(k * sizeof(int64_t)))) {
		fprintf(stderr, "error: Cannot allocate memory for vector r1\n");
		goto err_free_h1;
	}
	if (!(r2 = (int64_t *) malloc(k * sizeof(int64_t)))) {
		fprintf(stderr, "error: Cannot allocate memory for vector r2\n");
		goto err_free_r1;
	}
	if (!(r1d = (int64_t *) malloc(k * sizeof(int64_t)))) {
		fprintf(stderr, "error: Cannot allocate memory for vector r1d\n");
		goto err_free_r2;
	}
	if (!(r2d = (int64_t *) malloc(k * sizeof(int64_t)))) {
		fprintf(stderr, "error: Cannot allocate memory for vector r2d\n");
		goto err_free_r1d;
	}
	if (!(s = (int64_t *) malloc(k * sizeof(int64_t)))) {
		fprintf(stderr, "error: Cannot allocate memory for vector s\n");
		goto err_free_r2d;
	}

	return 0;

err_free_r2d:
	free(r2d);
err_free_r1d:
	free(r1d);
err_free_r2:
	free(r2);
err_free_r1:
	free(r1);
err_free_h1:
	free(h1);
err_free_h0:
	free(h0);
err_free_Id:
	free(Id);
	return -1;
}

int main(int argc, char **argv)
{
	int ds;
	int64_t q0, q1, *aux;
	size_t i, m, ner;
	double tmp, tmp2;

	if (process_args(argc, argv) != 0)
		return 1;

	/* Parameters for the p-ary MDPC instance */
	d = 1;
	nId = 2 * d + 1;

	if (setup() != 0)
		return 1;
	if (decoder_init(q, k) != 0) {
		fprintf(stderr, "error: Cannot initialise decoder\n");
		clean();
		return 1;
	}

	/* Compute set Id */
	aux = Id;
	*(aux++) = 0;
	for (; d > 0; d--) {
		*(aux++) = d;
		*(aux++) = q - d;
	}
	/* Compute q0 and q1*/
	tmp = ((double) q) / nId;
	q0 = (modf(tmp, &tmp2) <= 0.5) ? (int64_t) floor(tmp)
	                               : (int64_t) ceil(tmp);
	tmp = ((double) q) / (nId * nId);
	q1 = (modf(tmp, &tmp2) <= 0.5) ? (int64_t) floor(tmp)
	                               : (int64_t) ceil(tmp);

	srand(time(0));

	ner = 0;
	for (m = 0; m < nmtx; m++) {
		/* Generate new matrix */
		vfq_ranset(h0, k, Id, nId);
		vfq_ranset(h1, k, Id, nId);
		*h0 = (q0 + (*h0)) % q;
		*h1 = (q1 + (*h1)) % q;
		/* Execute decoder imtx times */
		for (i = 0; i < imtx; i++) {
			printf("%zu\t%zu", m, i);
			vfq_ranset(r1, k, Id, nId);
			vfq_ranset(r2, k, Id, nId);
			mfq_smul_vfq(s, h0, h1, r1, r2, k, q);
			ds = decode(r1d, r2d, s, h0, h1, k, iter, q, q0);
			if (!ds || !vfq_iseq(r1, r1d, k) || !vfq_iseq(r2, r2d, k))
				ner++;
			printf("\t%d\t%zu\t%zu\n", ds, ner, m * imtx + i + 1);
		}
	}

	decoder_clean();
	clean();

	return 0;
}
