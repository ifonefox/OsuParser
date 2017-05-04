#include <stdio.h>
#include <stdlib.h>
#include "parse.h"
int main(int argc, char *argv[])
{
  FILE *ptr;
  char buffer[20];
  int version;
  int len;
  CollectionDB db;
  ptr = fopen("collection.db", "rb");
  parse_collectiondb(ptr, &db);
  /*printf("%d\n",db.version);*/
  /*printf("%d\n",db.len);*/
  printf("l:%x\n",db.collections[0].len);


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
  parse_collection(ptr,&(col[0]));
  return bytes;
}
int parse_collection(FILE *ptr, Collection *col){
  int bytes = 0;
  unsigned int len = 0;
  char temp;
  int i;
  String *name;
  String **beatmaps;
  name = malloc(sizeof(String));
  bytes += parse_string(ptr,name);
  for(i = 0; i < name->len; i++){
    printf("%x ",name->text[i]);
  }
  printf("\n");
  col->name = name;
  // I am assuming you have less than 65536 beatmaps per collection
  // Please don't make me parse ULEB128
  for(i = 0; i < sizeof(unsigned int); i++){
    fread(&temp, sizeof(char), 1, ptr);
    printf("temp:%x\n",temp);
    temp = temp << (8*i);
    printf("temp2:%x\n",temp);
    len += (unsigned int)temp;
    printf("len: %x\n",len);
  }
  bytes += sizeof(unsigned int);
  printf("%u\n", len);
  col->len = len;
  
  return bytes;
}
int parse_string(FILE *ptr, String *str){
  int bytes = 0;
  char type;
  char len;
  int i;
  char *text;
  fread(&type, sizeof(char), 1, ptr);
  bytes++;
  if(type == 0x00){
    return bytes;
  }
  fread(&len, sizeof(char), 1, ptr);
  bytes++;
  str->len = len;
  text = malloc(sizeof(char)*len);
  fread(text, sizeof(char), len, ptr);
  bytes += len;
  str->text = text;
  return bytes;
}
