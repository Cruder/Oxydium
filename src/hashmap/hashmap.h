#ifndef __HASHMAP_H__
#define __HASHMAP_H__
#include "../linked_list/linked_list.h"

#define HASHMAP_COUNT 256
// String hashcode
// s[0]*31^(n - 1) + s[1]*31^(n - 2) + ... + s[n - 1]

typedef struct Hashmap {
  LinkedList* elements[HASHMAP_COUNT];
} Hashmap;

Hashmap* hashmapCreate();
void     hashmapDestroy(Hashmap* map);

bool     hashmapContainsValue(Hashmap* map, char* str);
void     hashmapPut(Hashmap* map, char* str, double value, bool constant);
Node*    hashmapGet(Hashmap* map, char* str);
void     hashmapPrint(Hashmap* map);

#endif /* end of include guard: __HASHMAP_H__ */
