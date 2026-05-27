#include <stdio.h>
#include <stdlib.h>
#include "bst.h"

node *createNode(int data) {
  node *newNode = malloc(sizeof(node));
  if (!newNode) {
    perror("cant malloc this node! RETURNING NULL");
    return NULL;
  }
  newNode->data = data;
  newNode->left = NULL;
  newNode->right = NULL;
  return newNode;
}

node *insertNode(node *root, int data) {
  if (root == NULL) {
    return createNode(data);
  }

  if (data > root->data) {
    root->right = insertNode(root->right, data);
  } else {
    root->left = insertNode(root->left, data);
  }
  return root;
}

void displayLNR(node *root) {
  if (root != NULL) {
    displayLNR(root->left);
    printf("%d ", root->data);
    displayLNR(root->right);
  }
}

void displayLRN(node *root) {
  if (root != NULL) {
    displayLRN(root->left);
    displayLRN(root->right);
    printf("%d ", root->data);
  }
}

void displayRLN(node *root) {
  if (root != NULL) {
    displayLRN(root->right);
    displayLRN(root->left);
    printf("%d ", root->data);
  }
}

void displayRNL(node *root) {
  if (root != NULL) {
    displayLRN(root->right);
    printf("%d ", root->data);
    displayLRN(root->left);
  }
}

node *findMin(node *root) {
  if (root->left == NULL && root->right == NULL) {
    return root;
  }
  return findMin(root->left);
}

node *findMax(node *root) {
  if (root->left == NULL && root->right == NULL) {
    return root;
  }
  return findMax(root->right);
}

void findNumber(node *root, int data) {
  if (root == NULL) {
    printf("cant found number: %d", data);
    return;
  }

  if (root->data == data) {
    printf("found it!!!!!!\n");
    return; //exit now!!!!!!1
  }

  if (data > root->data) {
    findNumber(root->right, data);
  } else if (data < root->data) {
    findNumber(root->left, data);
  }
}

node *deleteNode(node *root, int data) {
  if (root == NULL)
    return root;

  if (root->data > data) {
    root->left = deleteNode(root->left, data);
  } else if (root->data < data) {
    root->right = deleteNode(root->right, data);
  } else {
    if (root->left == NULL) {
      node *temp = root->right;
      free(root);
      return temp;
    } else if (root->right == NULL) {
      node *temp = root->left;
      free(root);
      return temp;
    }
    node *getMin = findMin(root);
    root->data = getMin->data;
    root->right = deleteNode(root->right, data);
  }
  return root;
}

node *destroyTree(node *root) {

  if (root == NULL) {
    return NULL;
  }

  destroyTree(root->left);
  destroyTree(root->right);

  free(root);

  return root;
}
