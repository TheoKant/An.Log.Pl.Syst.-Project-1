#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include "../HEADERS/sort_join.h"

void rec_sort ( relation *rel , int start , int end , int bnum ) {
	int size = calculate_size( start , end ) ;

	if ( size <= 64000 ) {
		//quicksort
		printf ( "THIS IS WHERE WE QUICKSORT\n" ) ;
	}
	else {
		//CREATE OUR BUCKET
		tuple *hist = malloc ( 256 * sizeof ( tuple ) ) ; //Hist is size of 2^8 = 256
		hist = create_hist ( rel , start , end , bnum ) ;
	}

}













tuple *create_hist ( relation *rel , int start , int end , int bnum ) {
	int total_tuples = end - start + 1 ;

	uint64_t s_byte;
	uint64_t key;

	for (int i = start ; i <= end ; i++ ) {
		
		key = relation_getkey ( rel , i ) ;
		s_byte = key << ( bnum - 1 ) * 8 ;
		s_byte = s_byte >> 56 ;
		printf("KEY IS %ld\n" , s_byte ) ;

	}
}







int calculate_size ( int start , int end ) {
	/*  EXAMPLE : WHOLE RELATION <-- 60 tuples
		then start = 0 and end = 59
		so total_tuples = end - start + 1 ;
	*/
	int total_tuples = end - start + 1 ;

	/*  Each tuple contains a uint64_t key (8 bytes = 64 bits) and a uint64_t payload (8 bytes = 64 bits)
		so tuple_size = 128 bits
	*/
	int tuple_size = 128 ;
	int total_tuple_size = total_tuples * tuple_size ;
	return total_tuple_size ;
}