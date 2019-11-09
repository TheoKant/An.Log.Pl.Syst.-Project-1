#include "../HEADERS/tuple.h"


typedef struct relation {
	tuple *tuples;
	int num_tuples;
} relation ;

relation * relation_create ( relation * /*relation to be created*/ ) ;

relation * relation_createtuples ( relation * , int /*tota tuples of relation*/) ;



void relation_setkey ( relation * , int  /*position of tuple that we want to set*/ , uint64_t /*key we want to set*/ ) ;

uint64_t relation_getkey ( relation * , int /*position of tuple that we want to get*/) ;

void relation_setpayload ( relation * , int /*position of tuple that we want to set*/ , uint64_t /*payload we want to set*/ ) ;

uint64_t relation_getpayload ( relation * , int tup /*position of tuple that we want to get*/) ;

int relation_getnumtuples ( relation * ) ;

int relation_checkifsorted ( relation *  ) ;