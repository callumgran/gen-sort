/*
 *  Copyright (C) 2023 Callum Gran
 *
 *  This program is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation, either version 3 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this program.  If not, see <https://www.gnu.org/licenses/>.
 */

#ifndef INSERTIONSORT_H
#define INSERTIONSORT_H

#include <stddef.h>
#include <stdint.h>
#include <sys/types.h>

#include "base_insertionsort.h"
#include "gen_insertionsort.h"

INIT_PRIMITIVE_INSERTIONSORT(int8_t, int8);
INIT_PRIMITIVE_INSERTIONSORT(int16_t, int16);
INIT_PRIMITIVE_INSERTIONSORT(int32_t, int32);
INIT_PRIMITIVE_INSERTIONSORT(int64_t, int64);
INIT_PRIMITIVE_INSERTIONSORT(uint8_t, uint8);
INIT_PRIMITIVE_INSERTIONSORT(uint16_t, uint16);
INIT_PRIMITIVE_INSERTIONSORT(uint32_t, uint32);
INIT_PRIMITIVE_INSERTIONSORT(uint64_t, uint64);
INIT_PRIMITIVE_INSERTIONSORT(double, double);
INIT_PRIMITIVE_INSERTIONSORT(float, float);
INIT_PRIMITIVE_INSERTIONSORT(long double, long_double);

#define CREATE_INSERTIONSORT_WRAPPER(type, compare_fn, insertionsort_fn)                  \
    void insertionsort_fn##_wrapper(type *base, type *bound, size_t size, compare_fn cmp) \
    {                                                                                     \
	insertionsort_fn(base, bound, cmp);                                               \
    }

CREATE_INSERTIONSORT_WRAPPER(int8_t, int8_compare_fn_t, insertionsort_int8);
CREATE_INSERTIONSORT_WRAPPER(int16_t, int16_compare_fn_t, insertionsort_int16);
CREATE_INSERTIONSORT_WRAPPER(int32_t, int32_compare_fn_t, insertionsort_int32);
CREATE_INSERTIONSORT_WRAPPER(int64_t, int64_compare_fn_t, insertionsort_int64);
CREATE_INSERTIONSORT_WRAPPER(uint8_t, uint8_compare_fn_t, insertionsort_uint8);
CREATE_INSERTIONSORT_WRAPPER(uint16_t, uint16_compare_fn_t, insertionsort_uint16);
CREATE_INSERTIONSORT_WRAPPER(uint32_t, uint32_compare_fn_t, insertionsort_uint32);
CREATE_INSERTIONSORT_WRAPPER(uint64_t, uint64_compare_fn_t, insertionsort_uint64);
CREATE_INSERTIONSORT_WRAPPER(double, double_compare_fn_t, insertionsort_double);
CREATE_INSERTIONSORT_WRAPPER(float, float_compare_fn_t, insertionsort_float);
CREATE_INSERTIONSORT_WRAPPER(long double, long_double_compare_fn_t, insertionsort_long_double);

#define INSERTIONSORT(start, end, cmp) \
    _Generic((start), int8_t *                    \
        : insertionsort_int8_wrapper, int16_t *      \
        : insertionsort_int16_wrapper, int32_t *     \
        : insertionsort_int32_wrapper, int64_t *     \
        : insertionsort_int64_wrapper, uint8_t *     \
        : insertionsort_uint8_wrapper, uint16_t *    \
        : insertionsort_uint16_wrapper, uint32_t *   \
        : insertionsort_uint32_wrapper, uint64_t *   \
        : insertionsort_uint64_wrapper, double *     \
        : insertionsort_double_wrapper, float *      \
        : insertionsort_float_wrapper, long double * \
        : insertionsort_long_double_wrapper, default \
        : insertionsort_generic)((start), (end), sizeof(*start), (cmp))

#endif // INSERTIONSORT_H