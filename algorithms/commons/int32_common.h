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

#ifndef INT32_SORTING_COMMON_H
#define INT32_SORTING_COMMON_H

#include <stdint.h>

#define INT32_SWAP(a, b)             \
    do {                             \
	register int32_t tmp = *(a); \
	*(a) = *(b);                 \
	*(b) = (tmp);                \
    } while (0)

#define THREE_INT32_ROTATE(a, b, c)  \
    do {                             \
	register int32_t tmp = *(a); \
	*(a) = *(b);                 \
	*(b) = *(c);                 \
	*(c) = (tmp);                \
    } while (0)

typedef int int32_compare_fn_t(int32_t a, int32_t b);

#endif