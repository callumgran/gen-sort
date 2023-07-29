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

#include "int8_bubblesort.h"
#include <stdint.h>
#include <stdlib.h>

static void bubblesort_int8_internal(int8_t *left, int8_t *right, int8_compare_fn_t cmp)
{
    for (int8_t *i = right; i > left; i--)
	for (int8_t *j = left; j < i; j++)
	    if ((*cmp)(*i, *j) < 0)
		INT8_SWAP(i, j);
}

inline void bubblesort_int8(int8_t *base, int8_t *bound, int8_compare_fn_t cmp)
{
    if (base == bound)
	return;

    int8_t *base_ptr = base;
    int8_t *bound_ptr = bound;
    bubblesort_int8_internal(base_ptr, bound_ptr, cmp);
}