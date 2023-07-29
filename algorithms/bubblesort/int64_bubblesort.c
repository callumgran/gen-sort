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

#include "int64_bubblesort.h"
#include <stdint.h>
#include <stdlib.h>

static void bubblesort_int64_internal(int64_t *left, int64_t *right, int64_compare_fn_t cmp)
{
    for (int64_t *i = right; i > left; i--)
	for (int64_t *j = left; j < i; j++)
	    if ((*cmp)(*i, *j) < 0)
		INT64_SWAP(i, j);
}

inline void bubblesort_int64(int64_t *base, int64_t *bound, int64_compare_fn_t cmp)
{
    if (base == bound)
	return;

    int64_t *base_ptr = base;
    int64_t *bound_ptr = bound;
    bubblesort_int64_internal(base_ptr, bound_ptr, cmp);
}