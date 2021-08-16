/*
 * File:   fqla.h
 * Author: Canales-Martinez, Isaac Andres
 */

#ifndef FQLA_H
#define FQLA_H

#include <stdint.h>
#include <stdio.h>

/**
 * vfq_add()
 *
 *   Add two vectors with coefficients modulo q.
 *
 * @dest:    pointer to the vector to store the result in
 * @a:       pointer to the addend
 * @b:       pointer to the addend
 * @len:     length of the vectors
 * @q:       modulo
 *
 * Notes:
 *   It is assumed that:
 *     - dest, a and b are not null pointers, and
 *     - the coefficients of a and b are integers between 0 and q-1, inclusive.
 */
void vfq_add(int64_t *dest, const int64_t *a, const int64_t *b, size_t len,
             int64_t q);

/**
 * vfq_sub()
 *
 *   Subtract one vector from another with coefficients modulo q.
 *
 * @dest:    pointer to the vector to store the result in
 * @a:       pointer to the minuend
 * @b:       pointer to the subtrahend
 * @len:     length of the vectors
 * @q:       modulo
 *
 * Notes:
 *   It is assumed that:
 *     - dest, a and b are not null pointers, and
 *     - the coefficients of a and b are integers between 0 and q-1, inclusive.
 */
void vfq_sub(int64_t *dest, const int64_t *a, const int64_t *b, size_t len,
             int64_t q);

/**
 * vfq_iseq()
 *
 *   Decide whether a vector is equal to another vector.
 *
 * @a:      pointer to the first vector
 * @b:      pointer to the second vector
 * @len:    length of the vectors
 *
 * Return:
 *   1 if the vectors are equal, 0 otherwise.
 *
 * Notes:
 *   It is assumed that:
 *     - a and b are not null pointers, and
 *     - the coefficients of a and b are integers between 0 and q-1, inclusive.
 */
int vfq_iseq(const int64_t *a, const int64_t *b, size_t len);

/**
 * vfq_iszero()
 *
 *   Decide whether a vector is the zero vector.
 *
 * @a:      pointer to the vector
 * @len:    length of the vector
 *
 * Return:
 *   1 if the vector is equal to the zero vector, 0 otherwise.
 *
 * Notes:
 *   It is assumed that:
 *     - a is not a null pointer, and
 *     - the coefficients of a are integers between 0 and q-1, inclusive.
 */
int vfq_iszero(const int64_t *a, size_t len);

/**
 * vfq_fprint()
 *
 *   Write a vector to a given output stream.
 *
 * @stream:    output file stream to write to
 * @a:         pointer to the vector
 * @len:       length of the vector
 *
 * Notes:
 *   It is assumed that stream and a are not null pointers.
 */
void vfq_fprint(FILE *stream, const int64_t *a, size_t len);

#endif /* FQLA_H */
