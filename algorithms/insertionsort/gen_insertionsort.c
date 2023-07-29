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

#include <stdint.h>
#include <stdlib.h>
#include <string.h>

#include "gen_insertionsort.h"

static void insertionsort_internal(uint8_t *left, uint8_t *right, size_t size, compare_fn_t cmp)
{
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

void insertionsort_generic(const void *base, const void *bound, size_t size, compare_fn_t cmp)
{
    if (base == bound)
	return;

    uint8_t *base_ptr = (uint8_t *)base;
    uint8_t *bound_ptr = (uint8_t *)bound;
    insertionsort_internal(base_ptr, bound_ptr, size, cmp);
}