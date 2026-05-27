#include <stdlib.h>
#include "bst.h"

int main() {

  node *root = NULL;

  for (size_t i = 0; i < 1000; i++) {
    root = insertNode(root, i);
  }

  displayLRN(root);
  deleteNode(root, 28);
  displayLRN(root);

  root = destroyTree(root);
  root = NULL;

  return EXIT_SUCCESS;
}
