/*
 * File:   fqla_util.h
 * Author: Canales-Martinez, Isaac Andres
 */

#ifndef FQLA_UTIL_H
#define FQLA_UTIL_H

#include <stddef.h>
#include <stdint.h>

/**
 * vfq_ranset()
 *
 *   Set a random value to a vector. This is done by setting each component of
 *   the vector to a randomly selected element from a given set.
 *
 * @dest:    pointer to the vector to store the result in
 * @len:     length of the vector
 * @S:       pointer to the set (array) from which the values will be selected
 * @lenS:    length of S
 *
 * Notes:
 *   It is assumed that:
 *     - dest and S are not null pointers, and
 *     - the elements of S are integers between 0 and q-1, inclusive.
 */
void vfq_ranset(int64_t *dest, size_t len, const int64_t *S, size_t lenS);

/**
 * vfq_ranbset()
 *
 *   Set a random balanced value to a vector. This is done by setting each
 *   component of the vector to a randomly selected element from a given set.
 *   Let v denote the vector and S denote the set, then the number of times each
 *   element of S appears in v will be
 *
 *   round(len(v) / card(S)) - t
 *
 *   for some tolerance parameter t.
 *
 * @dest:    pointer to the vector to store the result in
 * @len:     length of the vector
 * @S:       pointer to the set (array) from which the values will be selected
 * @lenS:    length of S
 * @t:       tolerance
 *
 * Notes:
 *   It is assumed that:
 *     - dest and S are not null pointers, and
 *     - the elements of S are integers between 0 and q-1, inclusive.
 */
void vfq_ranbset(int64_t *dest, size_t len, const int64_t *S, size_t lenS,
                 size_t t);

/**
 * mfq_smul_vfq()
 *
 *   Perform the matrix-vector multiplication
 *
 *   (M_0 | M_1) * (a_0 | a_1)^T
 *
 *   where
 *     - (M_0 | M_1) is a matrix defined by two vectors. Each of these vectors
 *       define a block of the matrix. Each block can be obtained by performing
 *       cyclic shifts of its defining vector, and
 *     - (a_0 | a_1) is a vector composed of two subvectors.
 *
 * @dest:    pointer to the vector to store the result in
 * @m0:      pointer to the vector defining the first matrix block
 * @m1:      pointer to the vector defining the second matrix block
 * @a0:      pointer to the vector defining the first subvector
 * @a1:      pointer to the vector defining the second subvector
 * @len:     length of the vectors
 * @q:       modulo
 *
 * Notes:
 *   It is assumed that:
 *     - dest, m0, m1, a0 and a1 are not null pointers, and
 *     - the coefficients of m0, m1, a0 and a1 are integers between 0 and q-1,
 *       inclusive.
 *   The pointer dest should not be equal to m0, m1, a0 or a1.
 */
void mfq_smul_vfq(int64_t *dest, const int64_t *m0, const int64_t *m1,
                  const int64_t *a0, const int64_t *a1, size_t len, int64_t q);

#endif /* FQLA_UTIL_H */
