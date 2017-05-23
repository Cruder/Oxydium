#include "hashmap.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <math.h>

#define FORMAP for(size_t i = 0; i < HASHMAP_COUNT; ++i)

int stringHashcode(char* str);

Hashmap* hashmapCreate() {
  Hashmap* map = (Hashmap*) malloc(sizeof(Hashmap));
  FORMAP {
      map->elements[i] = linkedListCreate();
  }

  return map;
}

void hashmapDestroy(Hashmap* map) {
  FORMAP {
    linkedListDestroy(map->elements[i]);
  }

  free(map);
  map = NULL;
}

bool hashmapContainsValue(Hashmap* map, char* str) {
  return hashmapGet(map, str) == NULL ? false : true;
}

void hashmapPut(Hashmap* map, char* str, double value) {
  Node* node = hashmapGet(map, str);
  if(node) {
    node->value = value;
  } else {
    LinkedList* list = map->elements[stringHashcode(str) % HASHMAP_COUNT];
    linkedListPut(list, str, value);
  }
}

Node* hashmapGet(Hashmap* map, char* str) {
  LinkedList* list = map->elements[stringHashcode(str) % HASHMAP_COUNT];
  return linkedListGet(list, str);
}

int stringHashcode(char* str) {
  if(str == NULL) { return 0; }
  int result = 0;
  size_t len = strlen(str);
  for(size_t i = 0; i < len; ++i) {
    result += str[0] * pow(31, len - i);
  }
  return result;
}

void hashmapPrint(Hashmap* map) {
  printf("HashMap [\n");
  FORMAP {
    if(map->elements[i]->size > 0) {
      printf("[%zu] -> ", i);
      linkedListPrint(map->elements[i]);
    }
  }
  printf("]\n");
}
