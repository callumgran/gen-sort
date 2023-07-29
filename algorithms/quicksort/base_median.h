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

#ifndef BASE_PRIMITIVE_MEDIAN_H
#define BASE_PRIMITIVE_MEDIAN_H

#include "../commons/base_common.h"
#include <stdint.h>
#include <stdlib.h>

#define INIT_PRIMITIVE_MEDIAN_THREE(type, name)                                 \
    type *name##_median_three(type *left, type *right, name##_compare_fn_t cmp) \
    {                                                                           \
	type *mid = left + ((right - left) >> 1);                               \
	if (cmp(*mid, *left) < 0) {                                             \
	    if (cmp(*right, *left) < 0) {                                       \
		if (cmp(*right, *mid) < 0) {                                    \
		    SWAP(type, left, right);                                    \
		} else {                                                        \
		    ROTATE(type, left, mid, right);                             \
		}                                                               \
	    } else {                                                            \
		SWAP(type, left, mid);                                          \
	    }                                                                   \
	} else {                                                                \
	    if ((*cmp)(*right, *mid) < 0) {                                     \
		if ((*cmp)(*right, *left) < 0) {                                \
		    ROTATE(type, right, mid, left);                             \
		} else {                                                        \
		    SWAP(type, mid, right);                                     \
		}                                                               \
	    }                                                                   \
	}                                                                       \
	return mid;                                                             \
    }

#define INIT_PRIMITIVE_MEDIAN_FIVE_OF_THREE(type, name)                                 \
    type *name##_median_five_of_three(type *left, type *right, name##_compare_fn_t cmp) \
    {                                                                                   \
	uint32_t half = ((right - left) >> 1);                                          \
	uint32_t quarter = half >> 1;                                                   \
	type *t_first_quart = left + quarter;                                           \
	type *t_mid = left + half;                                                      \
	type *t_third_quart = right - quarter;                                          \
	type *left_mid = name##_median_three(left, t_first_quart, cmp);                 \
	type *mid = name##_median_three(t_first_quart, t_mid, cmp);                     \
	type *right_mid = name##_median_three(t_mid, t_third_quart, cmp);               \
	if ((*cmp)(*left_mid, *left) < 0)                                               \
	    SWAP(type, left, left_mid);                                                 \
	if ((*cmp)(*right, *right_mid) < 0)                                             \
	    SWAP(type, right_mid, right);                                               \
	if ((*cmp)(*right_mid, *left) < 0)                                              \
	    SWAP(type, left, right_mid);                                                \
	if ((*cmp)(*right, *left_mid) < 0)                                              \
	    SWAP(type, left_mid, right);                                                \
	if ((*cmp)(*right_mid, *mid) < 0)                                               \
	    SWAP(type, mid, right_mid);                                                 \
	if ((*cmp)(*mid, *left_mid) < 0)                                                \
	    SWAP(type, left_mid, mid);                                                  \
	if ((*cmp)(*right_mid, *mid) < 0)                                               \
	    SWAP(type, right_mid, mid);                                                 \
	return mid;                                                                     \
    }

#define INIT_PRIMITIVE_MEDIAN_FIVE_OF_FIFTEEN(type, name)                                 \
    type *name##_median_five_of_fifteen(type *left, type *right, name##_compare_fn_t cmp) \
    {                                                                                     \
	uint32_t half = ((right - left) >> 1);                                            \
	uint32_t quarter = half >> 1;                                                     \
	type *t_first_quart = left + quarter;                                             \
	type *t_mid = left + half;                                                        \
	type *t_third_quart = right - quarter;                                            \
	type *left_mid = name##_median_five_of_three(left, t_first_quart, cmp);           \
	type *mid = name##_median_five_of_three(t_first_quart, t_mid, cmp);               \
	type *right_mid = name##_median_five_of_three(t_mid, t_third_quart, cmp);         \
	if ((*cmp)(*left_mid, *left) < 0)                                                 \
	    SWAP(type, left, left_mid);                                                   \
	if ((*cmp)(*right, *right_mid) < 0)                                               \
	    SWAP(type, right_mid, right);                                                 \
	if ((*cmp)(*right_mid, *left) < 0)                                                \
	    SWAP(type, left, right_mid);                                                  \
	if ((*cmp)(*right, *left_mid) < 0)                                                \
	    SWAP(type, left_mid, right);                                                  \
	if ((*cmp)(*right_mid, *mid) < 0)                                                 \
	    SWAP(type, mid, right_mid);                                                   \
	if ((*cmp)(*mid, *left_mid) < 0)                                                  \
	    SWAP(type, left_mid, mid);                                                    \
	if ((*cmp)(*right_mid, *mid) < 0)                                                 \
	    SWAP(type, right_mid, mid);                                                   \
	return mid;                                                                       \
    }

#endif /* BASE_PRIMITIVE_MEDIAN_H */