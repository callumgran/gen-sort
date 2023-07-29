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
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "../algorithms/bubblesort/bubblesort.h"

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

    int8_t arr_8[20];
    int16_t arr_16[20];
    int32_t arr_32[20];
    int64_t arr_64[20];
    float arr_float[20];
    double arr_double[20];
    struct tuple_t arr_tuple[20];

    for (int i = 0; i < 20; i++) {
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
    BUBBLESORT(arr_8, arr_8 + 19, int8_compare);
    for (int i = 0; i < 20; i++) {
	printf("%d ", arr_8[i]);
    }
    printf("\n");

    printf("Testing for int16_t:\n");
    BUBBLESORT(arr_16, arr_16 + 19, int16_compare);
    for (int i = 0; i < 20; i++) {
	printf("%d ", arr_16[i]);
    }
    printf("\n");

    printf("Testing for int32_t:\n");
    BUBBLESORT(arr_32, arr_32 + 19, int32_compare);
    for (int i = 0; i < 20; i++) {
	printf("%d ", arr_32[i]);
    }
    printf("\n");

    printf("Testing for int64_t:\n");
    BUBBLESORT(arr_64, arr_64 + 19, int64_compare);
    for (int i = 0; i < 20; i++) {
	printf("%ld ", arr_64[i]);
    }
    printf("\n");

    printf("Testing for float:\n");
    BUBBLESORT(arr_float, arr_float + 19, float_compare);
    for (int i = 0; i < 20; i++) {
    printf("%.2f ", arr_float[i]);
    }
    printf("\n");

    printf("Testing for double:\n");
    BUBBLESORT(arr_double, arr_double + 19, double_compare);
    for (int i = 0; i < 20; i++) {
    printf("%.2f ", arr_double[i]);
    }
    printf("\n");

    printf("Testing for struct tuple_t:\n");
    BUBBLESORT(arr_tuple, arr_tuple + 19, tuple_compare_int);
    for (int i = 0; i < 20; i++) {
	printf("%d ", arr_tuple[i].a);
    }
    printf("\n");

    return 0;
}