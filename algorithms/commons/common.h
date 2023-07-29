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

#ifndef SORTING_COMMON_H
#define SORTING_COMMON_H

#include <stdbool.h>
#include <stdint.h>
#include <string.h>

#include "../commons/base_common.h"

INIT_PRIMITVE_COMPARE_FN(int8_t, int8);
INIT_PRIMITVE_COMPARE_FN(int16_t, int16);
INIT_PRIMITVE_COMPARE_FN(int32_t, int32);
INIT_PRIMITVE_COMPARE_FN(int64_t, int64);
INIT_PRIMITVE_COMPARE_FN(uint8_t, uint8);
INIT_PRIMITVE_COMPARE_FN(uint16_t, uint16);
INIT_PRIMITVE_COMPARE_FN(uint32_t, uint32);
INIT_PRIMITVE_COMPARE_FN(uint64_t, uint64);
INIT_PRIMITVE_COMPARE_FN(float, float);
INIT_PRIMITVE_COMPARE_FN(double, double);
INIT_PRIMITVE_COMPARE_FN(long double, long_double);


#define BYTE_SWAP(a, b, size)              \
    do {                                   \
	size_t __size = (size);            \
	register uint8_t *__a = (a);       \
	register uint8_t *__b = (b);       \
	do {                               \
	    register uint8_t __tmp = *__a; \
	    *__a++ = *__b;                 \
	    *__b++ = __tmp;                \
	} while (--__size > 0);            \
    } while (0)

#define THREE_BYTE_ROTATE(a, b, c, size)   \
    do {                                   \
	size_t __size = (size);            \
	register uint8_t *__a = (a);       \
	register uint8_t *__b = (b);       \
	register uint8_t *__c = (c);       \
	do {                               \
	    register uint8_t __tmp = *__a; \
	    *__a++ = *__b;                 \
	    *__b++ = *__c;                 \
	    *__c++ = __tmp;                \
	} while (--__size > 0);            \
    } while (0)

#define FIND_MID(high, low, size) (size * ((high - left) / size >> 1))

#define FIND_FIRST_QUART(high, low, size) (size * (((high - low) / size) >> 2))

#define FIND_THIRD_QUART(high, low, size) (size * (((3 * (high - low)) / size) >> 2))

#define FIND_THIRD(high, low, size) (size * (((high - low) / size) / 3))

#define RUN_INSERTION(size) (27 * size)

#define MIN(a, b) ((a) < (b) ? (a) : (b))

#define MAX(a, b) ((a) > (b) ? (a) : (b))

typedef int compare_fn_t(const void *a, const void *b);

#endif // SORTING_COMMON_H