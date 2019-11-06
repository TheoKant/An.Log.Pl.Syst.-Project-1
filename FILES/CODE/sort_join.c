#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include "../HEADERS/sort_join.h"


// Function rec_sort used to sort the array

void rec_sort ( relation *rel , int start , int end , int bnum ) {
	int size = calculate_size( start , end ) ;

	if ( size <= 64000 ) {
		//quicksort
	
	}
	else {
		//Create hist for the part of the relation we are checking
		int *hist = malloc ( 256 * sizeof ( int ) ) ; //Hist is size of 2^8 = 256
		hist = create_hist ( rel , hist , start , end , bnum ) ; //scan the relation and fill the hist
		//Check which cells of hist arent 0 so we can determine the size of psum then fill it according to the given hist
		int psum_size = get_psumsize( hist );
		int **psum = malloc ( psum_size * sizeof ( int ) ) ;
		for (int i = 0 ; i < psum_size ; i++ ){
			psum[i] = malloc (2 * sizeof ( int ) ) ;
		}
		fill_psum ( psum , hist , psum_size );

		for ( int i = 0 ; i < psum_size ; i++ ){
			printf("BYTE IS %d AND IT STARTS FROM %d\n", psum[i][0],psum[i][1] );
		}
	}

}

//Fill psum according to given hist

void fill_psum ( int **psum , int *hist , int psum_size ) {
	int i = 0; //idenitifier for psum array
	int carry = 0; //carries the hist value of the last checked so we can add it to the next

	for ( int h = 0 ; h < 255 ; h++ ) {
		if ( hist[h] != 0 ) {
			if ( i == 0 ) { //first cell of psum starts from zero
				psum[i][0] = h;
				psum[i][1] = 0; 
				carry = hist[h] ;
				i++;
			}
			else { //ist cell of psum starts from last cell + last cells carry
				psum[i][0] = h;
				psum[i][1] = psum[i-1][1] + carry;
				carry = hist[h] ;
				i++;
			}
		}
	}
}

//Returns requiered size for the psum

int get_psumsize ( int *hist ) {
	int psum_size = 0;
	for (int i = 0 ; i <= 255 ; i++ ) {
		if ( hist[i] != 0 ) {
			psum_size++;
		}
	}
	return psum_size;
}

//Create Hist

int *create_hist ( relation *rel , int *hist , int start , int end , int bnum ) {

	uint64_t s_byte;
	uint64_t key;

	//Set all of hist cells to 0
	for (int h = start ; h <= 255 ; h++ ) {
		hist[h] = 0;
	}
	//Check all of the relation's tuples' bnum significant byte and add 1 to the matching hist cell
	for (int i = start ; i <= end ; i++ ) {
		key = relation_getkey ( rel , i ) ;
		s_byte = get_sigbyte ( key , bnum ) ;
		hist[s_byte]++;
	}
	return hist; 
}

//Returns i significant byte of the key

uint64_t get_sigbyte ( uint64_t key , int i ) {
	uint64_t s_byte = key << ( i - 1 ) * 8 ;
	s_byte = s_byte >> 56 ;
	return s_byte;
}

//Calculate size (bytes) of sub-relation

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