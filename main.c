#include "parse.h"
#include <stdlib.h>
#include <stdio.h>
int main(int argc, char *argv[])
{
  char* filename;
  CollectionDB db;
  FILE *ptr;
  if(argc < 2){
    printf("Assuming default filename (collection.db");
    filename = "collection.db";
  } else {
    filename = argv[1];
  }
  ptr = fopen(filename, "rb");
  parse_collectiondb(ptr, &db);
  print_collectiondb(&db);

  return 0;


}
