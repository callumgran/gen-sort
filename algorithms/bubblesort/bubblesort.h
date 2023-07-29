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

#ifndef BUBBLESORT_H
#define BUBBLESORT_H

#include <stddef.h>
#include <stdint.h>

#include "gen_bubblesort.h"
#include "int16_bubblesort.h"
#include "int32_bubblesort.h"
#include "int64_bubblesort.h"
#include "int8_bubblesort.h"

void bubblesort_int8_wrapper(int8_t *base, int8_t *bound, size_t size, int8_compare_fn_t cmp)
{
    bubblesort_int8(base, bound, cmp);
}

void bubblesort_int16_wrapper(int16_t *base, int16_t *bound, size_t size, int16_compare_fn_t cmp)
{
    bubblesort_int16(base, bound, cmp);
}

void bubblesort_int32_wrapper(int32_t *base, int32_t *bound, size_t size, int32_compare_fn_t cmp)
{
    bubblesort_int32(base, bound, cmp);
}

void bubblesort_int64_wrapper(int64_t *base, int64_t *bound, size_t size, int64_compare_fn_t cmp)
{
    bubblesort_int64(base, bound, cmp);
}

#define BUBBLESORT(start, end, cmp)                \
    _Generic((start), int8_t *                     \
	     : bubblesort_int8_wrapper, int16_t *  \
	     : bubblesort_int16_wrapper, int32_t * \
	     : bubblesort_int32_wrapper, int64_t * \
	     : bubblesort_int64_wrapper, default   \
	     : bubblesort_generic)((start), (end), sizeof(*start), (cmp))

#endif // BUBBLESORT_H