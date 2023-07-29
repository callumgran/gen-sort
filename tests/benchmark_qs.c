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

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "../algorithms/quicksort/quicksort.h"
#include "benchmark_commons.h"

#define SIZE (10000000)

static inline int cmp(int32_t a, int32_t b)
{
    return a - b;
}

static inline int cmp2(const void *a, const void *b)
{
    return *(int *)a - *(int *)b;
}

double generic_sort_with_time_ret(int *data)
{
    struct timespec start, end;
    double elapsed = 0;
    clock_gettime(CLOCK_MONOTONIC_RAW, &start);
    quicksort_generic(data, data + SIZE - 1, sizeof(int32_t), cmp2);
    clock_gettime(CLOCK_MONOTONIC_RAW, &end);
    elapsed += (end.tv_sec - start.tv_sec);
    elapsed += (end.tv_nsec - start.tv_nsec) / 1000000000.0;
    elapsed *= 1000;
    return elapsed;
}

double specified_sort_with_time_ret(int *data)
{
    struct timespec start, end;
    double elapsed = 0;
    clock_gettime(CLOCK_MONOTONIC_RAW, &start);
    QUICKSORT(data, data + SIZE - 1, cmp);
    clock_gettime(CLOCK_MONOTONIC_RAW, &end);
    elapsed += (end.tv_sec - start.tv_sec);
    elapsed += (end.tv_nsec - start.tv_nsec) / 1000000000.0;
    elapsed *= 1000;
    return elapsed;
}

double qsort_with_time_ret(int *data)
{
    struct timespec start, end;
    double elapsed = 0;
    clock_gettime(CLOCK_MONOTONIC_RAW, &start);
    qsort(data, SIZE, sizeof(int), cmp2);
    clock_gettime(CLOCK_MONOTONIC_RAW, &end);
    elapsed += (end.tv_sec - start.tv_sec);
    elapsed += (end.tv_nsec - start.tv_nsec) / 1000000000.0;
    elapsed *= 1000;
    return elapsed;
}

int main()
{
    srand(time(NULL));
    int32_t *data = (int32_t *)(malloc(SIZE * sizeof(int32_t)));
    int32_t *copy_arr = (int32_t *)(malloc(SIZE * sizeof(int32_t)));
    double elapsed_generic = 0;
    double elapsed_specific = 0;
    double elapsed_qsort = 0;

    printf("--------------------------------------------------------\n");
    printf("Random Numbers: %d million. \n\n", SIZE / 1000000);

    for (int i = 0; i < 10; i++) {
	fill_random(data, SIZE);

	copy(data, copy_arr, SIZE);
	elapsed_generic += generic_sort_with_time_ret(copy_arr);

	copy(data, copy_arr, SIZE);
	elapsed_specific += specified_sort_with_time_ret(copy_arr);

	copy(data, copy_arr, SIZE);
	elapsed_qsort += qsort_with_time_ret(copy_arr);
    }
    elapsed_generic /= 10;
    elapsed_specific /= 10;
    elapsed_qsort /= 10;

    printf("Average time taken for generic was: %fms\n", elapsed_generic);
    printf("Average time taken for specific was: %fms\n", elapsed_specific);
    printf("Average time taken for qsort was: %fms\n", elapsed_qsort);

    printf("--------------------------------------------------------\n");
    elapsed_generic = 0;
    elapsed_specific = 0;
    elapsed_qsort = 0;
    printf("--------------------------------------------------------\n");
    printf("Sqrt(%d) range Numbers: %d million. \n\n", SIZE, SIZE / 1000000);
    for (int i = 0; i < 10; i++) {
	fill_sqrt(data, SIZE);

	copy(data, copy_arr, SIZE);
	elapsed_generic += generic_sort_with_time_ret(copy_arr);

	copy(data, copy_arr, SIZE);
	elapsed_specific += specified_sort_with_time_ret(copy_arr);

	copy(data, copy_arr, SIZE);
	elapsed_qsort += qsort_with_time_ret(copy_arr);
    }
    elapsed_generic /= 10;
    elapsed_specific /= 10;
    elapsed_qsort /= 10;

    printf("Average time taken for generic was: %fms\n", elapsed_generic);
    printf("Average time taken for specific was: %fms\n", elapsed_specific);
    printf("Average time taken for qsort was: %fms\n", elapsed_qsort);

    printf("--------------------------------------------------------\n\n");
    elapsed_generic = 0;
    elapsed_specific = 0;
    elapsed_qsort = 0;
    printf("--------------------------------------------------------\n");
    printf("10 %% of %d range Numbers: %d million. \n\n", SIZE, SIZE / 1000000);
    for (int i = 0; i < 10; i++) {
	fill_10_percent(data, SIZE);

	copy(data, copy_arr, SIZE);
	elapsed_generic += generic_sort_with_time_ret(copy_arr);

	copy(data, copy_arr, SIZE);
	elapsed_specific += specified_sort_with_time_ret(copy_arr);

	copy(data, copy_arr, SIZE);
	elapsed_qsort += qsort_with_time_ret(copy_arr);
    }

    elapsed_generic /= 10;
    elapsed_specific /= 10;
    elapsed_qsort /= 10;

    printf("Average time taken for generic was: %fms\n", elapsed_generic);
    printf("Average time taken for specific was: %fms\n", elapsed_specific);
    printf("Average time taken for qsort was: %fms\n", elapsed_qsort);

    printf("--------------------------------------------------------\n\n");
    elapsed_generic = 0;
    elapsed_specific = 0;
    elapsed_qsort = 0;
    printf("--------------------------------------------------------\n");
    printf("Sorted Numbers: %d million. \n\n", SIZE / 1000000);
    for (int i = 0; i < 10; i++) {
	fill_sorted(data, SIZE);

	copy(data, copy_arr, SIZE);
	elapsed_generic += generic_sort_with_time_ret(copy_arr);

	copy(data, copy_arr, SIZE);
	elapsed_specific += specified_sort_with_time_ret(copy_arr);

	copy(data, copy_arr, SIZE);
	elapsed_qsort += qsort_with_time_ret(copy_arr);
    }

    elapsed_generic /= 10;
    elapsed_specific /= 10;
    elapsed_qsort /= 10;

    printf("Average time taken for generic was: %fms\n", elapsed_generic);
    printf("Average time taken for specific was: %fms\n", elapsed_specific);
    printf("Average time taken for qsort was: %fms\n", elapsed_qsort);

    printf("--------------------------------------------------------\n\n");
    elapsed_generic = 0;
    elapsed_specific = 0;
    elapsed_qsort = 0;
    printf("--------------------------------------------------------\n");
    printf("Reverse sorted Numbers: %d million. \n\n", SIZE / 1000000);
    for (int i = 0; i < 10; i++) {
	fill_reverse_sorted(data, SIZE);

	copy(data, copy_arr, SIZE);
	elapsed_generic += generic_sort_with_time_ret(copy_arr);

	copy(data, copy_arr, SIZE);
	elapsed_specific += specified_sort_with_time_ret(copy_arr);

	copy(data, copy_arr, SIZE);
	elapsed_qsort += qsort_with_time_ret(copy_arr);
    }

    elapsed_generic /= 10;
    elapsed_specific /= 10;
    elapsed_qsort /= 10;

    printf("Average time taken for generic was: %fms\n", elapsed_generic);
    printf("Average time taken for specific was: %fms\n", elapsed_specific);
    printf("Average time taken for qsort was: %fms\n", elapsed_qsort);

    printf("--------------------------------------------------------\n\n");
    elapsed_generic = 0;
    elapsed_specific = 0;
    elapsed_qsort = 0;
    printf("--------------------------------------------------------\n");
    printf("Half random Numbers: %d million. \n\n", SIZE / 1000000);
    for (int i = 0; i < 10; i++) {
	fill_half_random(data, SIZE);

	copy(data, copy_arr, SIZE);
	elapsed_generic += generic_sort_with_time_ret(copy_arr);

	copy(data, copy_arr, SIZE);
	elapsed_specific += specified_sort_with_time_ret(copy_arr);

	copy(data, copy_arr, SIZE);
	elapsed_qsort += qsort_with_time_ret(copy_arr);
    }

    elapsed_generic /= 10;
    elapsed_specific /= 10;
    elapsed_qsort /= 10;

    printf("Average time taken for generic was: %fms\n", elapsed_generic);
    printf("Average time taken for specific was: %fms\n", elapsed_specific);
    printf("Average time taken for qsort was: %fms\n", elapsed_qsort);

    printf("--------------------------------------------------------\n\n");
    elapsed_generic = 0;
    elapsed_specific = 0;
    elapsed_qsort = 0;
    printf("--------------------------------------------------------\n");
    printf("Low range Numbers: %d million. \n\n", SIZE / 1000000);
    for (int i = 0; i < 10; i++) {
	fill_small_range(data, SIZE);

	copy(data, copy_arr, SIZE);
	elapsed_generic += generic_sort_with_time_ret(copy_arr);

	copy(data, copy_arr, SIZE);
	elapsed_specific += specified_sort_with_time_ret(copy_arr);

	copy(data, copy_arr, SIZE);
	elapsed_qsort += qsort_with_time_ret(copy_arr);
    }

    elapsed_generic /= 10;
    elapsed_specific /= 10;
    elapsed_qsort /= 10;

    printf("Average time taken for generic was: %fms\n", elapsed_generic);
    printf("Average time taken for specific was: %fms\n", elapsed_specific);
    printf("Average time taken for qsort was: %fms\n", elapsed_qsort);

    printf("--------------------------------------------------------\n\n");

    free(data);
    free(copy_arr);

    return 0;
}