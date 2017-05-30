#include <stdio.h>
typedef struct Collection {
  char* name;
  unsigned int len;
  char** beatmaps;
} Collection;
typedef struct CollectionDB {
  int version;
  int len;
  Collection* collections;
} CollectionDB;
int parse_string(FILE *ptr, char **str);
int parse_collection(FILE *ptr, Collection *col);
int parse_collectiondb(FILE *ptr, CollectionDB *db);
void print_collectiondb(CollectionDB *db);
void print_collection(Collection *col);
