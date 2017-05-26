#include "hashmap.h"
#include <stdio.h>

int main(int argc, char const *argv[]) {
  Hashmap* map = hashmapCreate();

  hashmapPut(map, "bonjour?", 210.42, false);
  hashmapPut(map, "non!", 12.1, true);

  hashmapPrint(map);

  printf("non! => %lf\n", hashmapGet(map, "non!")->value);

  hashmapDestroy(map);

  return 0;
}
