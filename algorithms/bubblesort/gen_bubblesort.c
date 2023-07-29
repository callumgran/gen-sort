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

#include "gen_bubblesort.h"
#include <stdint.h>
#include <stdlib.h>

static void bubblesort_internal(uint8_t *left, uint8_t *right, size_t size, compare_fn_t cmp)
{
    for (uint8_t *i = right; i > left; i -= size)
	for (uint8_t *j = left; j < i; j += size)
	    if ((*cmp)(i, j) < 0)
		BYTE_SWAP(j, i, size);
}

inline void bubblesort_generic(const void *base, const void *bound, size_t size, compare_fn_t cmp)
{
    if (base == bound)
	return;

    uint8_t *base_ptr = (uint8_t *)base;
    uint8_t *bound_ptr = (uint8_t *)bound;
    bubblesort_internal(base_ptr, bound_ptr, size, cmp);
}