#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

#include "hashmap.h"

#define INITIAL_SIZE 11
#define LOAD_FACTOR 0.75

#define FNV1A_OFFSET_BASIS_64BITS 0xcbf29ce484222325
#define FNV1A_PRIME_64BITS 0x100000001b3

hashmap *createMap() {
  hashmap *newMap = malloc(sizeof(hashmap));
  if (!newMap) {
    perror("Fail: malloc'ed at createMap(). Return NULL!");
    return NULL;
  }
  newMap->capacity = INITIAL_SIZE;
  newMap->size = 0;
  newMap->table = calloc(newMap->capacity, sizeof(node *));
  if (!newMap->table) {
    perror("calloc failed at createMap(). Return NULL!");
    return NULL;
  }
  return newMap;
}

node *createNode(const char *key, int data) {
  node *newNode = malloc(sizeof(node));
  if (!newNode){
    perror("fail: malloc'ed at createNode. Return NULL! ");
    return NULL;
  }
  newNode->key = safeStrDup(key);
  newNode->data = data;
  newNode->freq = 1;
  newNode->next = NULL;

  return newNode;
}

void displayMapFull(hashmap *map) {

  if (!map)
    return;

  for (size_t i = 0; i < map->capacity; i++) {
    node *entry = map->table[i];
    while (entry) {
      printf("key: %s, data: %d, freq: %d->", entry->key, entry->data,
             entry->freq);
      entry = entry->next;
    }
    printf("NULL\n");
  }
}

void displayMap(hashmap *map) {

  if (!map)
    return;

  for (size_t i = 0; i < map->capacity; i++) {
    node *entry = map->table[i];
    while (entry) {
      printf("key: %s, data: %d, freq: %d\n", entry->key, entry->data,
             entry->freq);
      entry = entry->next;
    }
  }
}

char *safeStrDup(const char *key) {
  size_t len = strlen(key);
  char *keyDup = malloc((len + 1) * sizeof(char));
  if (!keyDup) {
    perror("failed at create space for key!");
    return NULL;
  }
  memcpy(keyDup, key, (len + 1));
  return keyDup;
}

void destroyMap(hashmap *map) {

  if (!map)
    return;

  for (size_t i = 0; i < map->capacity; i++) {
    node *entry = map->table[i];
    while (entry) {
      node *temp = entry;
      entry = entry->next;
      free(temp->key);
      free(temp);
    }
  }
  free(map->table);
  map->table = NULL;     //avoid dangling pointer case
  free(map);
  map = NULL;            //this too!!!!!!!!1
}

void deleteNode(hashmap *map, const char *key) {
  unsigned long index = fnv_1a(key, map->capacity);
  node *entry = map->table[index];
  node *prev = NULL;
  while (entry) {
    if (strcmp(entry->key, key) == 0) {
      if (prev) {
        prev->next = entry->next;
      } else {
        map->table[index] = entry->next;
      }
      free(entry->next);
      free(entry);
      map->size--;
      return;
    }
    prev = entry;
    entry = entry->next;
  }
  printf("cant find key to delete: %s not found!", key);
}

unsigned long fnv_1a(const char *key, int capacity) {
  uint32_t index = (uint32_t)FNV1A_OFFSET_BASIS_64BITS;
  while (*key++) {
    index ^= *key;
    index *= FNV1A_PRIME_64BITS;
  }
  return index % capacity;
}

void insertNode(hashmap *map, const char *key, int data) {

  if ((float)map->size / map->capacity >= (float)LOAD_FACTOR) {
    reSize(map);
  }

  unsigned long index = fnv_1a(key, map->capacity);
  node *entry = map->table[index];
  while (entry) {
    if (strcmp(entry->key, key) == 0) {
      entry->data = data;
      entry->freq++;
      return;
    }
    entry = entry->next;
  }
  node *newNode = createNode(key, data);
  newNode->next = map->table[index];
  map->table[index] = newNode;
  map->size++;
}

char *getLastestKeyByData(hashmap *map, int data) {
  node *tmp = NULL;
  for (size_t i = 0; i < map->capacity; i++) {
    node *entry = map->table[i];
    while (entry) {
      if (entry->data == data) {
        tmp = entry;
      }
      entry = entry->next;
    }
  }
  size_t len = strlen(tmp->key);
  char *result = malloc((len + 1) * sizeof(char));
  if (!result) {
      perror("error: cant malloc at getLastest() (OUT OF MEMORY)");
      return NULL;
  }
  memcpy(result, tmp->key, (len + 1));
  return result;
}

int getFreqByKey(hashmap *map, const char *key) {
  unsigned long index = fnv_1a(key, map->capacity);
  node *entry = map->table[index];
  while (entry) {
    if (strcmp(entry->key, key) == 0) {
      return entry->freq;
    }
    entry = entry->next;
  }
  printf("cant find: %s\n", key);
  return EXIT_FAILURE;
}

int getDataByKey(hashmap *map, const char *key) {
  unsigned long index = fnv_1a(key, map->capacity);
  node *entry = map->table[index];

  while (entry) {
    if (strcmp(entry->key, key) == 0) {
      return entry->data;
    }
    entry = entry->next;
  }
  printf("cant find: %s\n", key);
  return EXIT_FAILURE;
}

char **getArrayKeyByData(hashmap *map, int data, size_t *returnSize) {
  *returnSize = 0;
  char **arrayResult = NULL;

  for (size_t i = 0; i < map->capacity; i++) {
    node *entry = map->table[i];
    while (entry) {
      if (entry->data == data) {
        char **temp = realloc(arrayResult, (*returnSize + 1) * sizeof(char *));
        if (!temp) {
          for (size_t j = 0; j < *returnSize; j++){
            free(arrayResult[i]);
            free(arrayResult);
            return NULL;
          }
        }
        arrayResult = temp;
        arrayResult[(*returnSize)++] = safeStrDup(entry->key);
      }
      entry = entry->next;
    }
  }
  return arrayResult;
}

unsigned long sizes[] = {23,     47,      97,      197,     397,
                         797,    1597,    3203,    6421,    12853,
                         25717,  51437,   102877,  205759,  411527,
                         823117, 1646237, 3292489, 6584983, 13169977};

unsigned long nextSize(size_t capacity) {
  size_t size = sizeof(sizes) / sizeof(sizes[0]);
  for (size_t i = 0; i < size; i++) {
    if(capacity < sizes[i]) return sizes[i];
  }
  return capacity * 2 + 1;
}

void reSize(hashmap *map) {
  size_t oldSize = map->capacity;
  size_t newSize = nextSize(oldSize);

  node **oldTable = map->table;
  node **newTable = calloc(newSize, sizeof(node *));

  for (size_t i = 0; i < oldSize; i++) {
    node *entry = map->table[i];
    while (entry) {
      node *next = entry->next;
      unsigned long index = fnv_1a(entry->key, newSize);
      entry->next = newTable[index];
      newTable[index] = entry;
      entry = next;
    }
  }
  free(oldTable);
  map->table = newTable;
  map->capacity = newSize;
}
