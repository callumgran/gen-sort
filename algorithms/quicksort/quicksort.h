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

#ifndef QUICKSORT_H
#define QUICKSORT_H

#include <stddef.h>
#include <stdint.h>
#include <sys/types.h>

#include "../commons/common.h"
#include "base_median.h"
#include "base_quicksort.h"
#include "gen_quicksort.h"

INIT_PRIMITIVE_MEDIAN_THREE(int8_t, int8);
INIT_PRIMITIVE_MEDIAN_THREE(int16_t, int16);
INIT_PRIMITIVE_MEDIAN_THREE(int32_t, int32);
INIT_PRIMITIVE_MEDIAN_THREE(int64_t, int64);
INIT_PRIMITIVE_MEDIAN_THREE(uint8_t, uint8);
INIT_PRIMITIVE_MEDIAN_THREE(uint16_t, uint16);
INIT_PRIMITIVE_MEDIAN_THREE(uint32_t, uint32);
INIT_PRIMITIVE_MEDIAN_THREE(uint64_t, uint64);
INIT_PRIMITIVE_MEDIAN_THREE(float, float);
INIT_PRIMITIVE_MEDIAN_THREE(double, double);
INIT_PRIMITIVE_MEDIAN_THREE(long double, long_double);

INIT_PRIMITIVE_MEDIAN_FIVE_OF_THREE(int8_t, int8);
INIT_PRIMITIVE_MEDIAN_FIVE_OF_THREE(int16_t, int16);
INIT_PRIMITIVE_MEDIAN_FIVE_OF_THREE(int32_t, int32);
INIT_PRIMITIVE_MEDIAN_FIVE_OF_THREE(int64_t, int64);
INIT_PRIMITIVE_MEDIAN_FIVE_OF_THREE(uint8_t, uint8);
INIT_PRIMITIVE_MEDIAN_FIVE_OF_THREE(uint16_t, uint16);
INIT_PRIMITIVE_MEDIAN_FIVE_OF_THREE(uint32_t, uint32);
INIT_PRIMITIVE_MEDIAN_FIVE_OF_THREE(uint64_t, uint64);
INIT_PRIMITIVE_MEDIAN_FIVE_OF_THREE(float, float);
INIT_PRIMITIVE_MEDIAN_FIVE_OF_THREE(double, double);
INIT_PRIMITIVE_MEDIAN_FIVE_OF_THREE(long double, long_double);

INIT_PRIMITIVE_MEDIAN_FIVE_OF_FIFTEEN(int8_t, int8);
INIT_PRIMITIVE_MEDIAN_FIVE_OF_FIFTEEN(int16_t, int16);
INIT_PRIMITIVE_MEDIAN_FIVE_OF_FIFTEEN(int32_t, int32);
INIT_PRIMITIVE_MEDIAN_FIVE_OF_FIFTEEN(int64_t, int64);
INIT_PRIMITIVE_MEDIAN_FIVE_OF_FIFTEEN(uint8_t, uint8);
INIT_PRIMITIVE_MEDIAN_FIVE_OF_FIFTEEN(uint16_t, uint16);
INIT_PRIMITIVE_MEDIAN_FIVE_OF_FIFTEEN(uint32_t, uint32);
INIT_PRIMITIVE_MEDIAN_FIVE_OF_FIFTEEN(uint64_t, uint64);
INIT_PRIMITIVE_MEDIAN_FIVE_OF_FIFTEEN(float, float);
INIT_PRIMITIVE_MEDIAN_FIVE_OF_FIFTEEN(double, double);
INIT_PRIMITIVE_MEDIAN_FIVE_OF_FIFTEEN(long double, long_double);

INIT_PRIMITIVE_QUICKSORT(int8_t, int8);
INIT_PRIMITIVE_QUICKSORT(int16_t, int16);
INIT_PRIMITIVE_QUICKSORT(int32_t, int32);
INIT_PRIMITIVE_QUICKSORT(int64_t, int64);
INIT_PRIMITIVE_QUICKSORT(uint8_t, uint8);
INIT_PRIMITIVE_QUICKSORT(uint16_t, uint16);
INIT_PRIMITIVE_QUICKSORT(uint32_t, uint32);
INIT_PRIMITIVE_QUICKSORT(uint64_t, uint64);
INIT_PRIMITIVE_QUICKSORT(float, float);
INIT_PRIMITIVE_QUICKSORT(double, double);
INIT_PRIMITIVE_QUICKSORT(long double, long_double);

#define CREATE_QUICKSORT_WRAPPER(type, compare_fn, quicksort_fn)                      \
    void quicksort_fn##_wrapper(type *base, type *bound, size_t size, compare_fn cmp) \
    {                                                                                 \
	quicksort_fn(base, bound, cmp);                                               \
    }

CREATE_QUICKSORT_WRAPPER(int8_t, int8_compare_fn_t, quicksort_int8);
CREATE_QUICKSORT_WRAPPER(int16_t, int16_compare_fn_t, quicksort_int16);
CREATE_QUICKSORT_WRAPPER(int32_t, int32_compare_fn_t, quicksort_int32);
CREATE_QUICKSORT_WRAPPER(int64_t, int64_compare_fn_t, quicksort_int64);
CREATE_QUICKSORT_WRAPPER(uint8_t, uint8_compare_fn_t, quicksort_uint8);
CREATE_QUICKSORT_WRAPPER(uint16_t, uint16_compare_fn_t, quicksort_uint16);
CREATE_QUICKSORT_WRAPPER(uint32_t, uint32_compare_fn_t, quicksort_uint32);
CREATE_QUICKSORT_WRAPPER(uint64_t, uint64_compare_fn_t, quicksort_uint64);
CREATE_QUICKSORT_WRAPPER(double, double_compare_fn_t, quicksort_double);
CREATE_QUICKSORT_WRAPPER(float, float_compare_fn_t, quicksort_float);
CREATE_QUICKSORT_WRAPPER(long double, long_double_compare_fn_t, quicksort_long_double);

#define QUICKSORT(start, end, cmp) \
    _Generic((start), int8_t *                    \
        : quicksort_int8_wrapper, int16_t *      \
        : quicksort_int16_wrapper, int32_t *     \
        : quicksort_int32_wrapper, int64_t *     \
        : quicksort_int64_wrapper, uint8_t *     \
        : quicksort_uint8_wrapper, uint16_t *    \
        : quicksort_uint16_wrapper, uint32_t *   \
        : quicksort_uint32_wrapper, uint64_t *   \
        : quicksort_uint64_wrapper, double *     \
        : quicksort_double_wrapper, float *      \
        : quicksort_float_wrapper, long double * \
        : quicksort_long_double_wrapper, default \
        : quicksort_generic)((start), (end), sizeof(*start), (cmp))

#endif // QUICKSORT_H