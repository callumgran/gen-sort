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

#ifndef INT32_BUBBLESORT_H
#define INT32_BUBBLESORT_H

#include "../commons/int32_common.h"
#include <stdint.h>
#include <stdlib.h>

void bubblesort_int32(int32_t *base, int32_t *bound, int32_compare_fn_t cmp);

#endif // INT32_BUBBLESORT_H