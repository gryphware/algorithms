#include <stdio.h>
#include <stdbool.h>

void display_array(int *arr, size_t size){
  for(size_t i = 0; i < size; i++) printf("%d ", arr[i]);
  puts("");
}

void swap (int *a, int *b){
  *a += *b;
  *b = *a - *b;
  *a = *a - *b; 
}

void insertion(int *arr, size_t size){
  for(size_t i = 1; i < size; i++){
    size_t j = i - 1;
    int key = arr[i];
    bool is_swap = false;    
    while(j >= 0 && key < arr[j]){
      arr[j + 1] = arr[j];
      j--;
    }
    arr[j + 1] = key;    
  }
}
