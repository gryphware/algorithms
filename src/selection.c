#include "../include/selection.h"

#include <stdio.h>
#include <stdlib.h>

#define SIZE 7

int main(){

  int arr[SIZE] = {1, 3, 2, 5, 6, 7, 4}; 

  display_array(arr, SIZE);
  selection(arr, SIZE);
  display_array(arr, SIZE);
   
  return EXIT_SUCCESS;
}
