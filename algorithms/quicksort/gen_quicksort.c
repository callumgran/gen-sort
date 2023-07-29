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

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>

#include "gen_quicksort.h"

static inline uint8_t *median_three(uint8_t *left, uint8_t *right, const size_t size,
				    compare_fn_t cmp)
{
    uint8_t *mid = left + FIND_MID(right, left, size);

    if (cmp(mid, left) < 0) {
	if (cmp(right, left) < 0) {
	    if (cmp(right, mid) < 0) {
		BYTE_SWAP(left, right, size);
	    } else {
		THREE_BYTE_ROTATE(left, mid, right, size);
	    }
	} else {
	    BYTE_SWAP(left, mid, size);
	}
    } else {
	if ((*cmp)(right, mid) < 0) {
	    if ((*cmp)(right, left) < 0) {
		THREE_BYTE_ROTATE(right, mid, left, size);
	    } else {
		BYTE_SWAP(mid, right, size);
	    }
	}
    }

    return mid;
}

static inline uint8_t *median_five_of_three(uint8_t *left, uint8_t *right, const size_t size,
					    compare_fn_t cmp)
{
    int32_t half = FIND_MID(right, left, size);
    int32_t quarter = (size * ((half / size) >> 1));
    uint8_t *t_first_quart = left + quarter;
    uint8_t *t_mid = left + half;
    uint8_t *t_third_quart = right - quarter;

    uint8_t *left_mid = median_three(left, t_first_quart, size, cmp);

    uint8_t *mid = median_three(t_first_quart, t_mid, size, cmp);

    uint8_t *right_mid = median_three(t_mid, t_third_quart, size, cmp);

    if ((*cmp)(left_mid, left) < 0)
	BYTE_SWAP(left, left_mid, size);
    if ((*cmp)(right, right_mid) < 0)
	BYTE_SWAP(right_mid, right, size);
    if ((*cmp)(right_mid, left) < 0)
	BYTE_SWAP(left, right_mid, size);
    if ((*cmp)(right, left_mid) < 0)
	BYTE_SWAP(left_mid, right, size);
    if ((*cmp)(right_mid, mid) < 0)
	BYTE_SWAP(mid, right_mid, size);
    if ((*cmp)(mid, left_mid) < 0)
	BYTE_SWAP(left_mid, mid, size);
    if ((*cmp)(right_mid, mid) < 0)
	BYTE_SWAP(right_mid, mid, size);

    return mid;
}

static uint8_t *median_five_of_fifteen(uint8_t *left, uint8_t *right, size_t size, compare_fn_t cmp)
{
    int32_t half = FIND_MID(right, left, size);
    int32_t quarter = (size * ((half / size) >> 1));
    uint8_t *t_first_quart = left + quarter;
    uint8_t *t_mid = left + half;
    uint8_t *t_third_quart = right - quarter;

    uint8_t *left_mid = median_five_of_three(left, t_first_quart, size, cmp);

    uint8_t *mid = median_five_of_three(t_first_quart, t_mid, size, cmp);

    uint8_t *right_mid = median_five_of_three(t_mid, t_third_quart, size, cmp);

    if ((*cmp)(left_mid, left) < 0)
	BYTE_SWAP(left, left_mid, size);
    if ((*cmp)(right, right_mid) < 0)
	BYTE_SWAP(right_mid, right, size);
    if ((*cmp)(right_mid, left) < 0)
	BYTE_SWAP(left, right_mid, size);
    if ((*cmp)(right, left_mid) < 0)
	BYTE_SWAP(left_mid, right, size);
    if ((*cmp)(right_mid, mid) < 0)
	BYTE_SWAP(mid, right_mid, size);
    if ((*cmp)(mid, left_mid) < 0)
	BYTE_SWAP(left_mid, mid, size);
    if ((*cmp)(right_mid, mid) < 0)
	BYTE_SWAP(right_mid, mid, size);

    return mid;
}

static void dual_pivot_blockquicksort_rec(uint8_t *left, uint8_t *right, const size_t size,
					  compare_fn_t cmp)
{
    const ptrdiff_t  diff = right - left;

    if (right <= left)
	return;

    if (diff > RUN_INSERTION(size)) {
	uint32_t third = FIND_THIRD(right, left, size);

	uint8_t *third_1 = left + third;
	uint8_t *third_2 = right - third;

	const uint32_t min_diff_med_5 = 512 * size;

	const size_t size2x = size << 1;

	uint8_t *mid_1;
	uint8_t *mid_2;

	if (diff > 16384 * size) {
	    mid_1 = median_five_of_fifteen(left, third_2, size, cmp);
	    mid_2 = median_five_of_fifteen(third_1, right, size, cmp);
	} else if (third > min_diff_med_5) {
	    mid_1 = median_five_of_three(left, third_2, size, cmp);
	    mid_2 = median_five_of_three(third_1, right, size, cmp);
	} else {
	    mid_1 = median_three(left, third_2, size, cmp);
	    mid_2 = median_three(third_1, right, size, cmp);
	}

	if ((*cmp)(mid_1, mid_2) < 0) {
	    BYTE_SWAP(mid_1, left, size);
	    BYTE_SWAP(mid_2, right, size);
	} else {
	    BYTE_SWAP(mid_1, right, size);
	    BYTE_SWAP(mid_2, left, size);
	}

	int32_t piv_unequal = cmp(left, right);

	uint8_t piv1[size];
	memcpy(piv1, left, size);

	uint8_t piv2[size];
	memcpy(piv2, right, size);

	uint8_t *l = left + size;
	uint8_t *r = right - size;

	const uint16_t block_size = DP_BLOCK * size;
	const bool min_diff_reached = third > block_size + size;

	if (min_diff_reached && piv_unequal) {
	    uint8_t *tmp_r = r;
	    uint8_t *offset_left[DP_BLOCK];
	    uint8_t *offset_right[DP_BLOCK];
	    uint8_t **num_left = offset_left;
	    uint8_t **num_right = offset_right;
	    const uint16_t block_x3 = block_size * 3 - 1;

	    do {
		uint8_t *l_lim = l + block_size;
		if (num_left == offset_left) {
		    uint8_t *pd = l;
		    do {
			*num_left = pd;
			num_left += (cmp(piv1, pd) < 1);
			pd += size;
		    } while (pd != l_lim);
		}

		uint8_t *r_lim = tmp_r - block_size;
		if (num_right == offset_right) {
		    uint8_t *pd = tmp_r;
		    do {
			*num_right = pd;
			num_right += (cmp(pd, piv1) < 0);
			pd -= size;
		    } while (pd != r_lim);
		}

		const uint32_t min = MIN(num_left - offset_left, num_right - offset_right);
		num_left -= min;
		num_right -= min;

		for (uint32_t i = 0; i < min; i++) {
		    BYTE_SWAP(*(num_left + i), *(num_right + i), size);
		}

		l += num_left == offset_left ? block_size : 0;
		tmp_r -= num_right == offset_right ? block_size : 0;
	    } while (tmp_r - l > block_x3);

	    uint8_t *tmp_l = l + size;
	    num_left = offset_left;
	    num_right = offset_right;

	    do {
		uint8_t *l_lim = tmp_l + block_size;
		if (num_left == offset_left) {
		    uint8_t *pd = tmp_l;
		    do {
			*num_left = pd;
			num_left += (cmp(piv2, pd) < 1);
			pd += size;
		    } while (pd != l_lim);
		}

		uint8_t *r_lim = r - block_size;
		if (num_right == offset_right) {
		    uint8_t *pd = r;
		    do {
			*num_right = pd;
			num_right += (cmp(pd, piv2) < 0);
			pd -= size;
		    } while (pd != r_lim);
		}

		const uint32_t min = MIN(num_left - offset_left, num_right - offset_right);
		num_left -= min;
		num_right -= min;

		for (uint32_t i = 0; i < min; i++) {
		    BYTE_SWAP(*(num_left + i), *(num_right + i), size);
		}

		tmp_l += num_left == offset_left ? block_size : 0;
		r -= num_right == offset_right ? block_size : 0;

	    } while (r - tmp_l > block_x3);
	}

	const ptrdiff_t pre_dist = r - l;

	for (uint8_t *l_1 = l; l_1 <= r; l_1 += size) {
	    if ((*cmp)(l_1, piv2) > 0) {
		while (l_1 < r && (*cmp)(r, piv2) > 0) {
		    r -= size;
		}

		if ((*cmp)(r, piv1) < 0) {
		    THREE_BYTE_ROTATE(r, l_1, l, size);
		    l += size;
		} else {
		    BYTE_SWAP(l_1, r, size);
		}
		r -= size;
	    } else if ((*cmp)(l_1, piv1) < 0) {
		BYTE_SWAP(l_1, l, size);
		l += size;
	    }
	}

	const ptrdiff_t dist = r - l;

	BYTE_SWAP(l - size, left, size);
	BYTE_SWAP(r + size, right, size);

	dual_pivot_blockquicksort_rec(left, l - size2x, size, cmp);
	dual_pivot_blockquicksort_rec(r + size2x, right, size, cmp);

	if (piv_unequal && dist > (pre_dist - 13 * size)) {
	    for (uint8_t *l_1 = l; l_1 <= r; l_1 += size) {
		if ((*cmp)(l_1, piv1) == 0) {
		    BYTE_SWAP(l_1, l, size);
		    l += size;
		} else if ((*cmp)(piv2, l_1) == 0) {
		    if ((*cmp)(r, piv1) == 0) {
			THREE_BYTE_ROTATE(r, l_1, l, size);
			l += size;
		    } else {
			BYTE_SWAP(l_1, r, size);
		    }
		    r -= size;
		}
	    }
	}

	if (piv_unequal) {
	    dual_pivot_blockquicksort_rec(l, r, size, cmp);
	}
    } else {
	for (uint8_t *i = left + size; i <= right; i += size)
	    if (cmp(i, left) < 0)
		BYTE_SWAP(i, left, size);

	for (uint8_t *i = left + (size << 1); i <= right; i += size) {
	    uint8_t high[size];
	    memcpy(high, i, size);
	    uint8_t *j = i - size;
	    while (cmp(high, j) < 0) {
		memcpy(j + size, j, size);
		j -= size;
	    }
	    memcpy(j + size, high, size);
	}
    }
}

inline void quicksort_generic(const void *base, const void *bound, const size_t size,
			      compare_fn_t cmp)
{
    if (base == bound)
	return;

    uint8_t *base_ptr = (uint8_t *)base;
    uint8_t *left_ptr = base_ptr;
    uint8_t *right_ptr = (uint8_t *)bound;
    dual_pivot_blockquicksort_rec(left_ptr, right_ptr, size, cmp);
}