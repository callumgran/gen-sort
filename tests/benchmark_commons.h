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

#ifndef BENCHMARK_COMMONS_H
#define BENCHMARK_COMMONS_H

#include <stdlib.h>

/**
 * Method to fill an array with random integers.
 * @param data The array to fill.
 * @param len The length of the array.
 */
void fill_random(int *data, int len);

/**
 * Method to fill an array with sorted integers.
 * @param data The array to fill.
 * @param len The length of the array.
 */
void fill_sorted(int *data, int len);

/**
 * Method to fill an array with reverse sorted integers.
 * @param data The array to fill.
 * @param len The length of the array.
 */
void fill_reverse_sorted(int *data, int len);

/**
 * Method to fill an array with half random integers.
 * @param data The array to fill.
 * @param len The length of the array.
 */
void fill_half_random(int *data, int len);

/**
 * Method to fill an array with integers in a small range.
 * @param data The array to fill.
 * @param len The length of the array.
 */
void fill_small_range(int *data, int len);

/**
 * Method to fill an array with integers in the range of the square root of the length.
 * @param data The array to fill.
 * @param len The length of the array.
 */
void fill_sqrt(int *data, int len);

/**
 * Method to fill an array with integers in 10% of the range of the length.
 * @param data The array to fill.
 * @param len The length of the array.
 */
void fill_10_percent(int *data, int len);

/**
 * Method to test if an array is sorted.
 * @param data The array to test.
 * @param len The length of the array.
 */
void test_sorted(int *data, int len);

/**
 * Method to sum an array of integers.
 * @param data The array to sum.
 * @param len The length of the array.
 * @return The sum of the array.
 */
long long sum_array(int *data, int len);

/**
 * Method to copy an array of integers.
 * @param data The array to copy.
 * @param copy The array to copy to.
 * @param len The length of the array.
 */
void copy(int *data, int *copy, int len);

/**
 * Method to compare two long long values.
 * @param sum1 The first value.
 * @param sum2 The second value.
 */
void test_values(long long sum1, long long sum2);

#endif // BENCHMARK_COMMONS_H