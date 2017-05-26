#include "linked_list.h"
#include <stdio.h>

int main(int argc, char const *argv[]) {
  LinkedList* list = linkedListCreate();
  linkedListPut(list, "bonjour?", 210.42, true);
  linkedListPut(list, "non!", 12.1, false);

  linkedListPrint(list);

  return 0;
}
