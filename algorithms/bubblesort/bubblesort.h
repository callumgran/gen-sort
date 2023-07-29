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

#ifndef BUBBLESORT_H
#define BUBBLESORT_H

#include <stddef.h>
#include <stdint.h>
#include <sys/types.h>

#include "base_bubblesort.h"
#include "gen_bubblesort.h"

INIT_PRIMITIVE_BUBBLESORT(int8_t, int8);
INIT_PRIMITIVE_BUBBLESORT(int16_t, int16);
INIT_PRIMITIVE_BUBBLESORT(int32_t, int32);
INIT_PRIMITIVE_BUBBLESORT(int64_t, int64);
INIT_PRIMITIVE_BUBBLESORT(uint8_t, uint8);
INIT_PRIMITIVE_BUBBLESORT(uint16_t, uint16);
INIT_PRIMITIVE_BUBBLESORT(uint32_t, uint32);
INIT_PRIMITIVE_BUBBLESORT(uint64_t, uint64);
INIT_PRIMITIVE_BUBBLESORT(double, double);
INIT_PRIMITIVE_BUBBLESORT(float, float);
INIT_PRIMITIVE_BUBBLESORT(long double, long_double);

#define CREATE_BUBBLESORT_WRAPPER(type, compare_fn, bubblesort_fn)                     \
    void bubblesort_fn##_wrapper(type *base, type *bound, size_t size, compare_fn cmp) \
    {                                                                                  \
	bubblesort_fn(base, bound, cmp);                                               \
    }

CREATE_BUBBLESORT_WRAPPER(int8_t, int8_compare_fn_t, bubblesort_int8);
CREATE_BUBBLESORT_WRAPPER(int16_t, int16_compare_fn_t, bubblesort_int16);
CREATE_BUBBLESORT_WRAPPER(int32_t, int32_compare_fn_t, bubblesort_int32);
CREATE_BUBBLESORT_WRAPPER(int64_t, int64_compare_fn_t, bubblesort_int64);
CREATE_BUBBLESORT_WRAPPER(uint8_t, uint8_compare_fn_t, bubblesort_uint8);
CREATE_BUBBLESORT_WRAPPER(uint16_t, uint16_compare_fn_t, bubblesort_uint16);
CREATE_BUBBLESORT_WRAPPER(uint32_t, uint32_compare_fn_t, bubblesort_uint32);
CREATE_BUBBLESORT_WRAPPER(uint64_t, uint64_compare_fn_t, bubblesort_uint64);
CREATE_BUBBLESORT_WRAPPER(double, double_compare_fn_t, bubblesort_double);
CREATE_BUBBLESORT_WRAPPER(float, float_compare_fn_t, bubblesort_float);
CREATE_BUBBLESORT_WRAPPER(long double, long_double_compare_fn_t, bubblesort_long_double);

#define BUBBLESORT(start, end, cmp) \
    _Generic((start), int8_t *                    \
        : bubblesort_int8_wrapper, int16_t *      \
        : bubblesort_int16_wrapper, int32_t *     \
        : bubblesort_int32_wrapper, int64_t *     \
        : bubblesort_int64_wrapper, uint8_t *     \
        : bubblesort_uint8_wrapper, uint16_t *    \
        : bubblesort_uint16_wrapper, uint32_t *   \
        : bubblesort_uint32_wrapper, uint64_t *   \
        : bubblesort_uint64_wrapper, double *     \
        : bubblesort_double_wrapper, float *      \
        : bubblesort_float_wrapper, long double * \
        : bubblesort_long_double_wrapper, default \
        : bubblesort_generic)((start), (end), sizeof(*start), (cmp))

#endif // BUBBLESORT_H