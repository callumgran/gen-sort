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

#include "int32_bubblesort.h"
#include <stdint.h>
#include <stdlib.h>

static void bubblesort_int32_internal(int32_t *left, int32_t *right, int32_compare_fn_t cmp)
{
    for (int32_t *i = right; i > left; i--)
	for (int32_t *j = left; j < i; j++)
	    if ((*cmp)(*i, *j) < 0)
		INT32_SWAP(i, j);
}

inline void bubblesort_int32(int32_t *base, int32_t *bound, int32_compare_fn_t cmp)
{
    if (base == bound)
	return;

    int32_t *base_ptr = base;
    int32_t *bound_ptr = bound;
    bubblesort_int32_internal(base_ptr, bound_ptr, cmp);
}