
#include <stdio.h>
#include <stdint.h>
#include <string.h>


#include "../HEADERS/main.h"


int main()
{


	List list;
	relation *R;
	relation *S;

	initlist(&list, MAXSIZE, sizeof(tuple));


	//sort_merge_join () ;

	join(R, S, &list);
	printf("The list created to hold the results contains %d equal relations divided into %d nodes.\n", ((list.tuples_size * --list.counter) + list.tail->current_position), list.counter);
	printf("Each node contains %d relations\n\n", list.tuples_size);

	R = relation_create( R ) ;
	S = relation_create( S ) ;

	read_file ( R , "/home/parallels/Desktop/Project/An.Log.Pl.Syst.-Project-1/FILES/Datasets/tiny/relA" ) ;
	read_file ( S , "/home/parallels/Desktop/Project/An.Log.Pl.Syst.-Project-1/FILES/Datasets/tiny/relB" ) ;

	int r = relation_getnumtuples( R ); //total tuples in r relation
	
	int s = relation_getnumtuples( S ); //total tuples in s relation
	


	rec_sort ( R , 0 , r-1 , 6 ) ; //FIRST WE SORT THE R RELATION

	// join(&R, &S, &list);
	// printf("The list created to hold the results contains %d equal relations divided into %d nodes.\n", ((list.tuples_size * --list.counter) + list.tail->current_position), list.counter);
	// printf("Each node contains %d relations\n\n", list.tuples_size);

}

void read_file ( relation * rel , char * file_name ) {


	//OPEN THE FILE 

	FILE *fp;
	fp = fopen ( file_name , "r");	

	if ( fp == NULL ) {
		perror("fopen");
		exit(EXIT_FAILURE);
	}


	//FIRST WE COUNT THE TUPLES THAT WELL NEED

	char *line = NULL;
    size_t len = 0;
    ssize_t nread;

    int total_tuples = 0 ; //TOTAL TUPLES



	while ( ( nread = getline( &line , &len , fp ) ) != -1 ) {
			total_tuples++;
	}

	printf("total tuples are %d\n" , total_tuples );

	free(line);

	fclose(fp);

	//CREATE THE RELATION WITH TOTAL TUPLES

	rel = relation_createtuples ( rel , total_tuples ) ;


	//THEN WE START FILLING THE RELATION

	fp = fopen ( file_name , "r");	

	if ( fp == NULL ) {
		perror("fopen");
		exit(EXIT_FAILURE);
	}
	
	line = NULL;
    len = 0;
    nread;
    int tup_no = 0;


	while ( ( nread = getline( &line , &len , fp ) ) != -1 ) {
			extract_line ( rel , line , tup_no ) ;
			tup_no++;
	}


	free(line);

	//CLOSE THE FILE

	fclose(fp);

}


void extract_line ( relation * rel , char * line , int tup_num ) {
	

	//printf ("STRING IS %s\n",line);

	char * key_string;
	char * payload_string;

	//FIRST EXTRACT THE KEY
	key_string = strtok ( line , " ," ) ;

	//SET THE KEY TO TUPLE NUMBER tup_num
	uint64_t key = strtoll(key_string, NULL, 10);
	relation_setkey( rel , tup_num , key ) ;

	//uint64_t test = relation_getkey(rel,tup_num);
	//printf("ORIGINAL %ld\nTEST " , key);
	//printf("%ld\n\n",test);


	//THEN EXTRACT THE PAYLOAD
	payload_string = strtok ( NULL , " ,\n" ) ;

	//SET THE PAYLOAD
	uint64_t payload = strtoll ( payload_string, NULL, 10 );
	relation_setpayload ( rel , tup_num , payload ) ;

	//uint64_t test2 = relation_getpayload(rel,tup_num);
	//printf("ORIGINAL payload %ld\nTEST " , payload);
	//printf("%ld\n\n",test2);

}