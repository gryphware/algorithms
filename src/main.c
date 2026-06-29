#include <stdio.h>
#include <stdlib.h>

#include "../include/bubble_sort.h"

int main() {

  int arr[] = {12, 4, 56, 76, 0, -2, 100};
  size_t len = sizeof(arr) / sizeof(arr[0]);
  print_array(arr, len);
  bubble(arr, len);
  print_array(arr, len);

  return EXIT_SUCCESS;
}
