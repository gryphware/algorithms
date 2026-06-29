typedef struct node {
  struct node *left;
  struct node *right;
  int data;
} node;

node *insertNode(node *root, int data);
node *createNode(int data);
void displayLNR(node *root);
void displayLRN(node *root);
void displayRLN(node *root);
void displayRNL(node *root);
node *findMax(node *root);
node *findMin(node *root);
void findNumber(node *root, int data);
node *deleteNode(node *root, int data);
node *destroyTree(node *root);
