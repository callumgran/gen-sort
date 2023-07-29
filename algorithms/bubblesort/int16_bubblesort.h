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

#ifndef INT16_BUBBLESORT_H
#define INT16_BUBBLESORT_H

#include "../commons/int16_common.h"
#include <stdint.h>
#include <stdlib.h>

void bubblesort_int16(int16_t *base, int16_t *bound, int16_compare_fn_t cmp);

#endif // INT16_BUBBLESORT_H