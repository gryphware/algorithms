#include <stdbool.h>
#include <stddef.h>
#include <stdio.h>

typedef struct node {
  char *key;
  int data;
  int freq;
  struct node *next;
} node;

typedef struct hashmap {
  node **table;
  size_t capacity;
  size_t size;
} hashmap;

unsigned long fnv_1a(const char *key, int capacity);
hashmap *createMap();
node *createNode(const char *key, int data);
void displayMapFull(hashmap *map);
void displayMap(hashmap *map);
void destroyMap(hashmap *map);
char *safeStrDup(const char *key);
void deleteNode(hashmap *map, const char *key);
void insertNode(hashmap *map, const char *key, int data);
char *
getLastestKeyByData(hashmap *map,
                    int data); // useless lol, who trying this unless you are me
int getFreqByKey(hashmap *map, const char *key);
int getDataByKey(hashmap *map, const char *key);
char **getArrayKeyByData(hashmap *map, int data,
                        size_t *returnSize); // THIS WILL USE A LOT OF MEMORY

unsigned long nextSize(size_t capacity);
void reSize(hashmap *map);
