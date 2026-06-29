#include <stdio.h>
#include <stdlib.h>

#include "../include/bubble_sort.h"

void print_array(int *arr, size_t len) {

  for (size_t i = 0; i < len; i++) {
    printf("%d ", arr[i]);
  }

  puts("");
}

void swap(int *a, int *b) {
  int temp = *a;
  *a = *b;
  *b = temp;
}

void bubble(int *arr, size_t len) {

  for (size_t i = 0; i < len; i++) {
    int swapped = 0;
    for (size_t j = 0; j < len - 1 - i; j++) {
      if (arr[j] > arr[j + 1]) {
        swap(&arr[j], &arr[j + 1]);
        swapped = 1;
      }
    }
    if(!swapped) return;
  }
}
