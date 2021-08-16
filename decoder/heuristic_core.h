/*
 * File:   heuristic_core.h
 * Author: Canales-Martinez, Isaac Andres
 */

#ifndef HEURISTIC_CORE_H
#define HEURISTIC_CORE_H

#include <stddef.h>
#include <stdint.h>

/**
 * decode()
 *
 *   Execute the decoding algorithm.
 *
 * @r1:       pointer to the fisrt vector to store the result in
 * @r2:       pointer to the second vector to store the result in
 * @s:        syndrome of the vector to decode
 * @h0:       pointer to the vector defining the first matrix block
 * @h1:       pointer to the vector defining the second matrix block
 * @k:        length of the vectors
 * @iter:     number of iterations
 * @delta:    parameter for computing the threshold
 * @q:        modulo
 * @q0:       value used for the significant part of h0
 * @P:        pointer to the set (array) of signal points
 * @nP:       length of P
 *
 * Return:
 *   1 if decoding is successful, 0 otherwise.
 *
 * Notes:
 *   It is assumed that:
 *     - r1, r2, s, h0, h1 and P are not null pointers, and
 *     - the elements of s, h0 and h1 are integers between 0 and q-1, inclusive.
 *   The pointers r1 and r2 should not be equal to s, h0, h1 or P.
 */
int decode(int64_t *r1, int64_t *r2, const int64_t *s, const int64_t *h0,
           const int64_t *h1, size_t k, size_t iter, int64_t delta, int64_t q,
           int64_t q0, const int64_t *P, size_t nP);

/**
 * decoder_init()
 *
 *   Initialise internal variables used by the decoding algorithm.
 *
 * @q:    modulo
 * @k:    length of the vectors
 *
 * Return:
 *   0 if initialisation is successful, a negative value otherwise.
 */
int decoder_init(int64_t q, size_t k);

/**
 * decoder_clean()
 *
 *   Free memory allocated during initialisation.
 */
void decoder_clean();

#endif /* HEURISTIC_CORE_H */
