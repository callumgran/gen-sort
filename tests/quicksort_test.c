/*
 *  Copyright (C) SIZE23 Callum Gran
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
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "../algorithms/quicksort/quicksort.h"

#define SIZE 50000

struct tuple_t {
    int32_t a;
    float b;
};

int int8_compare(int8_t a, int8_t b)
{
    return a - b;
}

int int16_compare(int16_t a, int16_t b)
{
    return a - b;
}

int int32_compare(int32_t a, int32_t b)
{
    return a - b;
}

int int64_compare(int64_t a, int64_t b)
{
    return a - b;
}

int float_compare(float a, float b)
{
    float diff = a - b;
    return diff < 0 ? -1 : diff > 0 ? 1 : 0;
}

int double_compare(double a, double b)
{
    double diff = a - b;
    return diff < 0 ? -1 : diff > 0 ? 1 : 0;
}

int tuple_compare_int(const void *a, const void *b)
{
    return ((struct tuple_t *)a)->a - ((struct tuple_t *)b)->a;
}

int main(void)
{
    srand(time(NULL));

    int8_t arr_8[SIZE];
    int16_t arr_16[SIZE];
    int32_t arr_32[SIZE];
    int64_t arr_64[SIZE];
    float arr_float[SIZE];
    double arr_double[SIZE];
    struct tuple_t arr_tuple[SIZE];

    for (int i = 0; i < SIZE; i++) {
	arr_8[i] = rand() % INT8_MAX;
	arr_16[i] = rand() % INT16_MAX;
	arr_32[i] = rand() % INT16_MAX;
	arr_64[i] = rand() % INT16_MAX;
	arr_float[i] = (float)rand() / (float)(RAND_MAX / INT16_MAX);
	arr_double[i] = (double)rand() / (double)(RAND_MAX / INT16_MAX);
	arr_tuple[i].a = rand() % INT16_MAX;
	arr_tuple[i].b = (float)rand() / (float)(RAND_MAX / INT16_MAX);
    }

    printf("Testing for int8_t:\n");
    QUICKSORT(arr_8, arr_8 + SIZE - 1, int8_compare);
    for (int i = 1; i < 50000; i++) {
	if (arr_8[i] < arr_8[i - 1]) {
	    printf("Failed at index %d\n", i);
	    break;
	}
    }
    printf("\n");

    printf("Testing for int16_t:\n");
    QUICKSORT(arr_16, arr_16 + SIZE - 1, int16_compare);
    for (int i = 1; i < SIZE; i++) {
	if (arr_16[i] < arr_16[i - 1]) {
	    printf("Failed at index %d\n", i);
	    break;
	}
    }
    printf("\n");

    printf("Testing for int32_t:\n");
    QUICKSORT(arr_32, arr_32 + SIZE - 1, int32_compare);
    for (int i = 1; i < SIZE; i++) {
	if (arr_32[i] < arr_32[i - 1]) {
	    printf("Failed at index %d\n", i);
	    break;
	}
    }
    printf("\n");

    printf("Testing for int64_t:\n");
    QUICKSORT(arr_64, arr_64 + SIZE - 1, int64_compare);
    for (int i = 1; i < SIZE; i++) {
	if (arr_64[i] < arr_64[i - 1]) {
	    printf("Failed at index %d\n", i);
	    break;
	}
    }
    printf("\n");

    printf("Testing for float:\n");
    QUICKSORT(arr_float, arr_float + SIZE - 1, float_compare);
    for (int i = 1; i < SIZE; i++) {
	if (arr_float[i] < arr_float[i - 1]) {
	    printf("Failed at index %d\n", i);
	    break;
	}
    }
    printf("\n");

    printf("Testing for double:\n");
    QUICKSORT(arr_double, arr_double + SIZE - 1, double_compare);
    for (int i = 1; i < SIZE; i++) {
	if (arr_double[i] < arr_double[i - 1]) {
	    printf("Failed at index %d\n", i);
	    break;
	}
    }
    printf("\n");

    printf("Testing for struct tuple_t:\n");
    QUICKSORT(arr_tuple, arr_tuple + SIZE - 1, tuple_compare_int);
    for (int i = 1; i < SIZE; i++) {
	if (arr_tuple[i].a < arr_tuple[i - 1].a) {
	    printf("Failed at index %d\n", i);
	    break;
	}
    }
    printf("\n");

    return 0;
}