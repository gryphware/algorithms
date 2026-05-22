#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include "hashmap.h"

int main() {

  hashmap *myMap = createMap();

  insertNode(myMap, "chanh", 20);
  insertNode(myMap, "help", 20);
  displayMap(myMap);

  size_t returnSize;

  char **array = getArrayKeyByData(myMap, 20, &returnSize);

  for (size_t i = 0; i < returnSize; i++) {
    printf("%s ", array[i]);
  }

  for (size_t i = 0; i < returnSize; i++) {
    free(array[i]);
  }
  free(array);
  destroyMap(myMap);
  return EXIT_SUCCESS;
}
