#include "../include/insertion.h"

#include <stdlib.h>

#define SIZE 5

int main(){

  int arr[SIZE] = {2, 4, 1, 6, 2};

  display_array(arr, SIZE);
  insertion(arr, SIZE);
  
  display_array(arr, SIZE);
  return EXIT_SUCCESS;
}
