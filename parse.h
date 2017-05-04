typedef struct String {
  int len; //replace with ULEB128
  char *text;
} String;
typedef struct Collection {
  String* name;
  unsigned int len;
  String** beatmaps;
} Collection;
typedef struct CollectionDB {
  int version;
  int len;
  Collection* collections;
} CollectionDB;
int parse_string(FILE *ptr, String *str);
int parse_collection(FILE *ptr, Collection *col);
int parse_collectiondb(FILE *ptr, CollectionDB *db);
