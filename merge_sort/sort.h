#ifndef SORT_H
#define SORT_H

#include <stdio.h>
#include <stdlib.h>

void merge_sort(int *array, size_t size);
void split_merge(int *array, int *tmp, size_t start, size_t end);
void do_merge(int *array, int *tmp, size_t start, size_t mid, size_t end);
void print_array(const int *array, size_t size);

#endif
