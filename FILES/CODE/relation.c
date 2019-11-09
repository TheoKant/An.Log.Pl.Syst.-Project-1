#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include "../HEADERS/relation.h"


relation * relation_create ( relation *this ) {
	this = malloc ( sizeof ( relation ) ) ;
	return this;
}

relation * relation_createtuples ( relation *this , int num /* number of tuples */ ) {
	//
	this->num_tuples = num ;
	//
	this->tuples = malloc ( num * sizeof(tuple) ) ;

	return this;
}


void relation_setkey( relation *this , int tup /*position of tuple that we want to set*/ , uint64_t key /*key we want to set*/ ) {
	
	tuple_setkey ( &this->tuples[tup] , key );

}

uint64_t relation_getkey ( relation *this , int tup /*position of tuple that we want to get*/) {
	
	uint64_t key = tuple_getkey ( &this->tuples[tup] );
	return key;

}




void relation_setpayload ( relation *this , int tup /*position of tuple that we want to set*/ , uint64_t payl /*payload we want to set*/ ) {
	
	tuple_setpayload ( &this->tuples[tup] , payl );

}

uint64_t relation_getpayload ( relation *this , int tup /*position of tuple that we want to get*/) {
	
	uint64_t payl = tuple_getpayload ( &this->tuples[tup] );
	return payl;

}

int relation_getnumtuples ( relation * this ) {
	return this->num_tuples ;
}
