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

#ifndef BASE_NUMERIC_BUBBLESORT_H
#define BASE_NUMERIC_BUBBLESORT_H

#include "../commons/base_common.h"
#include <stdint.h>
#include <stdlib.h>

#define INIT_PRIMITIVE_BUBBLESORT(type, name)                                \
    void bubblesort_##name(type *base, type *bound, name##_compare_fn_t cmp) \
    {                                                                        \
	if (base == bound)                                                   \
	    return;                                                          \
	for (type *i = bound; i > base; i--)                                 \
	    for (type *j = base; j < i; j++)                                 \
		if ((*cmp)(*i, *j) < 0)                                      \
		    SWAP(type, i, j);                                        \
    }

#endif // BASE_NUMERIC_BUBBLESORT_H