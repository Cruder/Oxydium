#include "linked_list.h"
#include <stdio.h>

int main(int argc, char const *argv[]) {
  LinkedList* list = linkedListCreate();
  linkedListPut(list, "bonjour?", 210.42);
  linkedListPut(list, "non!", 12.1);

  linkedListPrint(list);

  return 0;
}
