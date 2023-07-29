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

#ifndef DPBLOCKSORT_H
#define DPBLOCKSORT_H

#define RUN_INSERTION(size) (27 * size)
#define DP_BLOCK 256

#include "../commons/common.h"

void quicksort_generic(const void *base, const void *bound, const size_t size, compare_fn_t cmp);

#endif // DP_BLOCKSORT_H