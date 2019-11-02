#ifndef MAIN_H
#define MAIN_H



#include <stdio.h>
#include <stdint.h>
#include "list.h"

#define MAXSIZE 200//1048576

struct list;

typedef struct tuple {
	int64_t key;
	int64_t payload;
}Tuple;

typedef struct  {
	Tuple *tuples;
	uint64_t num_tuples;
}relation;


void join(relation *relR, relation *relS,  struct list *list);

int isEqual(relation *relR, relation *relS, int i, int k);

relation getRelationR(relation R);

relation getRelationS(relation S);

relation getRelation(relation rel);

void printRelation(relation rel);

 #endif