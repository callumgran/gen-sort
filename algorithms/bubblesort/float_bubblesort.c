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

#include "float_bubblesort.h"
#include <stdint.h>
#include <stdlib.h>

static void bubblesort_float_internal(float *left, float *right, float_compare_fn_t cmp)
{
    for (float *i = right; i > left; i--)
	for (float *j = left; j < i; j++)
	    if ((*cmp)(*i, *j) < 0)
		FLOAT_SWAP(i, j);
}

inline void bubblesort_int8(float *base, float *bound, float_compare_fn_t cmp)
{
    if (base == bound)
	return;

    float *base_ptr = base;
    float *bound_ptr = bound;
    bubblesort_float_internal(base_ptr, bound_ptr, cmp);
}