#include <stdio.h>

//swap things
void swap(int *a, int *b){
  *a += *b;
  *b = *a - *b;
  *a = *a - *b;
}

//for display for nothing
void display_array(int *arr, size_t size){
  for(size_t i = 0; i < size; i++){
    printf("%d ", arr[i]);
  }
  puts("");
}

//this is main algorithms
void selection(int *arr, unsigned int size){
  for(size_t i = 0; i < size; i++){
    unsigned int min_index = i;
    for(size_t j = i + 1; j < size; j++){
      if (arr[min_index] > arr[j]){
        min_index = j;
      }
    }
    if(min_index != i) swap(&arr[i], &arr[min_index]);
  }
}


