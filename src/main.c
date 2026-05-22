#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include "hashmap.h"

int main() {

  hashmap *myMap = createMap();

  char buffer[122];

  //test for hyperfine
  for (size_t i = 0; i < 100000; i++) {
    sprintf(buffer, "buffer %zu\n", i);
    insertNode(myMap, buffer, i);
  }

  printf("%zu", myMap->capacity);

  destroyMap(myMap);

  return EXIT_SUCCESS;
}
