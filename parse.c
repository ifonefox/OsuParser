#include <stdio.h>
#include <stdlib.h>
#include "parse.h"
int main(int argc, char *argv[]) {
  FILE *ptr;
  CollectionDB db;
  ptr = fopen("collection.db", "rb");
  parse_collectiondb(ptr, &db);
  for (int i = 0; i < db.len; i++) {
    printf("final name:%s\n",db.collections[i].name);
  }
  return 0;
}
int parse_collectiondb(FILE *ptr, CollectionDB *db){
  int bytes = 0;
  int version;
  int len;
  Collection *col;
  //get version
  fread(&version, sizeof(int),1,ptr);
  bytes += sizeof(int);
  db->version = version;
  //get number of collections
  fread(&len, sizeof(int),1,ptr);
  bytes += sizeof(int);
  db->len = len;
  col = malloc(sizeof(Collection) * len);
  db->collections = col;
  for (int i = 0; i < len; i++) {
    parse_collection(ptr,col+i); //address of col[i]
  }
  return bytes;
}
int parse_collection(FILE *ptr, Collection *col){
  int bytes = 0;
  unsigned int len = 0;
  char temp;
  unsigned int i;
  char* name;
  char** beatmaps;
  name = malloc(sizeof(String));
  bytes += parse_string(ptr,&name);
  col->name = name;
  // I am assuming you have less than 65536 beatmaps per collection
  // Please don't make me parse ULEB128
  for(i = 0; i < sizeof(unsigned int); i++){
    fread(&temp, sizeof(char), 1, ptr);
    temp = temp << (8*i);
    len += (unsigned int)temp;
  }
  bytes += sizeof(unsigned int);
  col->len = len;
  beatmaps = malloc(sizeof(char*)*len);
  for (i = 0; i < len; i++) {
    parse_string(ptr, &(beatmaps[i])); //address of beatmaps[i]
  }
  col->beatmaps = beatmaps;
  
  return bytes;
}
int parse_string(FILE *ptr, char** str){
  int bytes = 0;
  char type;
  char len;
  char *text;
  fread(&type, sizeof(char), 1, ptr);
  bytes++;
  if(type == 0x00){
    *str = NULL;
    return bytes;
  }
  fread(&len, sizeof(char), 1, ptr);
  bytes++;
  text = malloc(sizeof(char)*(len+1));
  fread(text, sizeof(char), len, ptr);
  text[len] = '\0';
  bytes += len;
  *str = text;
  return bytes;
}
