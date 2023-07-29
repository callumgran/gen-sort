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

#ifndef BASE_PRIMITIVE_QUICKSORT_H
#define BASE_PRIMITIVE_QUICKSORT_H

#include <stddef.h>
#include <stdint.h>

#include "../commons/base_common.h"

#define MIN_INSERTION 27
#define MIN_MEDIAN_5 512
#define MIN_MEDIAN_5_OF_15 16384
#define DP_BLOCK_SIZE 256
#define TRIPLE_DP_BLOCK_SIZE 767

#define INIT_PRIMITIVE_QUICKSORT(type, name)                                                    \
    void quicksort_##name(type *left, type *right, name##_compare_fn_t cmp)                     \
    {                                                                                           \
	const ptrdiff_t diff = right - left;                                                    \
	if (right <= left)                                                                      \
	    return;                                                                             \
	if (diff > MIN_INSERTION) {                                                             \
	    uint32_t third = diff / 3;                                                          \
	    type *third_1 = left + third;                                                       \
	    type *third_2 = right - third;                                                      \
	    type *mid_1;                                                                        \
	    type *mid_2;                                                                        \
	    if (diff > MIN_MEDIAN_5_OF_15) {                                                    \
		mid_1 = name##_median_five_of_fifteen(left, third_2, cmp);                      \
		mid_2 = name##_median_five_of_fifteen(third_1, right, cmp);                     \
	    } else if (third > MIN_MEDIAN_5) {                                                  \
		mid_1 = name##_median_five_of_three(left, third_2, cmp);                        \
		mid_2 = name##_median_five_of_three(third_1, right, cmp);                       \
	    } else {                                                                            \
		mid_1 = name##_median_three(left, third_2, cmp);                                \
		mid_2 = name##_median_three(third_1, right, cmp);                               \
	    }                                                                                   \
	    if ((*cmp)(*mid_1, *mid_2) < 0) {                                                   \
		SWAP(type, mid_1, left);                                                        \
		SWAP(type, mid_2, right);                                                       \
	    } else {                                                                            \
		SWAP(type, mid_1, right);                                                       \
		SWAP(type, mid_2, left);                                                        \
	    }                                                                                   \
	    int32_t piv_unequal = cmp(*left, *right);                                           \
	    type piv1 = *left;                                                                  \
	    type piv2 = *right;                                                                 \
	    type *l = left + 1;                                                                 \
	    type *r = right - 1;                                                                \
	    const bool min_diff_reached = third > DP_BLOCK_SIZE;                                \
	    if (min_diff_reached && piv_unequal) {                                              \
		type *tmp_r = r;                                                                \
		type *offset_left[DP_BLOCK_SIZE];                                               \
		type *offset_right[DP_BLOCK_SIZE];                                              \
		type **num_left = offset_left;                                                  \
		type **num_right = offset_right;                                                \
		do {                                                                            \
		    type *l_lim = l + DP_BLOCK_SIZE;                                            \
		    if (num_left == offset_left) {                                              \
			type *pd = l;                                                           \
			do {                                                                    \
			    *num_left = pd;                                                     \
			    num_left += (cmp(piv1, *pd) < 1);                                   \
			    pd++;                                                               \
			} while (pd != l_lim);                                                  \
		    }                                                                           \
		    type *r_lim = tmp_r - DP_BLOCK_SIZE;                                        \
		    if (num_right == offset_right) {                                            \
			type *pd = tmp_r;                                                       \
			do {                                                                    \
			    *num_right = pd;                                                    \
			    num_right += (cmp(*pd, piv1) < 0);                                  \
			    pd--;                                                               \
			} while (pd != r_lim);                                                  \
		    }                                                                           \
		    const uint32_t min = MIN(num_left - offset_left, num_right - offset_right); \
		    num_left -= min;                                                            \
		    num_right -= min;                                                           \
		    for (uint32_t i = 0; i < min; i++) {                                        \
			SWAP(type, *(num_left + i), *(num_right + i));                          \
		    }                                                                           \
		    l += num_left == offset_left ? DP_BLOCK_SIZE : 0;                           \
		    tmp_r -= num_right == offset_right ? DP_BLOCK_SIZE : 0;                     \
		} while (tmp_r - l > TRIPLE_DP_BLOCK_SIZE);                                     \
		type *tmp_l = l;                                                                \
		num_left = offset_left;                                                         \
		num_right = offset_right;                                                       \
		do {                                                                            \
		    type *l_lim = tmp_l + DP_BLOCK_SIZE;                                        \
		    if (num_left == offset_left) {                                              \
			type *pd = tmp_l;                                                       \
			do {                                                                    \
			    *num_left = pd;                                                     \
			    num_left += (cmp(piv2, *pd) < 1);                                   \
			    pd++;                                                               \
			} while (pd != l_lim);                                                  \
		    }                                                                           \
		    type *r_lim = r - DP_BLOCK_SIZE;                                            \
		    if (num_right == offset_right) {                                            \
			type *pd = r;                                                           \
			do {                                                                    \
			    *num_right = pd;                                                    \
			    num_right += (cmp(*pd, piv2) < 0);                                  \
			    pd--;                                                               \
			} while (pd != r_lim);                                                  \
		    }                                                                           \
		    const uint32_t min = MIN(num_left - offset_left, num_right - offset_right); \
		    num_left -= min;                                                            \
		    num_right -= min;                                                           \
		    for (uint32_t i = 0; i < min; i++) {                                        \
			SWAP(type, *(num_left + i), *(num_right + i));                          \
		    }                                                                           \
		    tmp_l += num_left == offset_left ? DP_BLOCK_SIZE : 0;                       \
		    r -= num_right == offset_right ? DP_BLOCK_SIZE : 0;                         \
		} while (r - tmp_l > TRIPLE_DP_BLOCK_SIZE);                                     \
	    }                                                                                   \
	    const ptrdiff_t pre_dist = r - l;                                                   \
	    for (type *l_1 = l; l_1 <= r; l_1++) {                                              \
		if ((*cmp)(*l_1, piv2) > 0) {                                                   \
		    while (l_1 < r && (*cmp)(*r, piv2) > 0) {                                   \
			r--;                                                                    \
		    }                                                                           \
		    if ((*cmp)(*r, piv1) < 0) {                                                 \
			ROTATE(type, r, l_1, l);                                                \
			l++;                                                                    \
		    } else {                                                                    \
			SWAP(type, l_1, r);                                                     \
		    }                                                                           \
		    r--;                                                                        \
		} else if ((*cmp)(*l_1, piv1) < 0) {                                            \
		    SWAP(type, l_1, l);                                                         \
		    l++;                                                                        \
		}                                                                               \
	    }                                                                                   \
	    const ptrdiff_t dist = r - l;                                                       \
	    SWAP(type, l - 1, left);                                                            \
	    SWAP(type, r + 1, right);                                                           \
	    quicksort_##name(left, l - 2, cmp);                                                 \
	    quicksort_##name(r + 2, right, cmp);                                                \
	    if (piv_unequal && dist > (pre_dist - 13)) {                                        \
		for (type *l_1 = l; l_1 <= r; l_1++) {                                          \
		    if ((*cmp)(*l_1, piv1) == 0) {                                              \
			SWAP(type, l_1, l);                                                     \
			l++;                                                                    \
		    } else if ((*cmp)(piv2, *l_1) == 0) {                                       \
			if ((*cmp)(*r, piv1) == 0) {                                            \
			    ROTATE(type, r, l_1, l);                                            \
			    l++;                                                                \
			} else {                                                                \
			    SWAP(type, l_1, r);                                                 \
			}                                                                       \
			r--;                                                                    \
		    }                                                                           \
		}                                                                               \
	    }                                                                                   \
	    if (piv_unequal) {                                                                  \
		quicksort_##name(l, r, cmp);                                                    \
	    }                                                                                   \
	} else {                                                                                \
	    for (type *i = left + 1; i <= right; i++)                                           \
		if (cmp(*i, *left) < 0)                                                         \
		    SWAP(type, i, left);                                                        \
	    for (type *i = left + 2; i <= right; i++) {                                         \
		type high;                                                                      \
		high = *i;                                                                      \
		type *j = i - 1;                                                                \
		while (cmp(high, *j) < 0) {                                                     \
		    *(j + 1) = *j;                                                              \
		    j--;                                                                        \
		}                                                                               \
		*(j + 1) = high;                                                                \
	    }                                                                                   \
	}                                                                                       \
    }

#endif