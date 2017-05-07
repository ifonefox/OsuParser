//
//  ced.c
//  OsuParser
//
//  Created by Sean Brody on 5/6/17.
//  Copyright © 2017 Sean Brody. All rights reserved.
//

#include "ced.h"
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
