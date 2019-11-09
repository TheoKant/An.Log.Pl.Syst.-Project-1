#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include "../HEADERS/sort_join.h"


// Function rec_sort used to sort the array

void rec_sort ( relation *rel , int start , int end , int bpos ) {
	int total_tuples = count_tuples ( start , end ) ;
	int size = calculate_size( total_tuples ) ;

	if ( size <= 64000 ) {
		//quicksort
	}
	else {
		//Create hist for the part of the relation we are checking
		int *hist = malloc ( 256 * sizeof ( int ) ) ; //Hist is size of 2^8 = 256
		hist = create_hist ( rel , hist , start , end , bpos ) ; //scan the relation and fill the hist
		
		//Check which cells of hist aren't 0 so we can determine the size of psum then fill it according to the given hist
		int psum_size = get_psumsize( hist ); 
		int **psum = malloc ( psum_size * sizeof ( int * ) ) ;
		for (int i = 0 ; i < psum_size ; i++ ){
			psum[i] = malloc (2 * sizeof ( int ) ) ;
		}
		fill_psum ( psum , hist , psum_size );

		//Now rearrange the part that we work in this recursive level with the help of the empty temp relation
		relation *temp;
		temp = relation_create ( temp ) ; //Give space
		rearrange ( rel , temp , start , total_tuples , bpos , psum , psum_size ) ;

		//Free Memory
		free(temp);
		free(hist);
		for ( int i = 0 ; i < psum_size ; i++ ){
			free(psum[i]);
		}
		free(psum);
	}

}

//Rearrange our relation with help of temp relation

void rearrange ( relation *rel , relation *temp , int start , int total_tuples , int bpos , int **psum , int psum_size ) {
	temp = relation_createtuples ( temp , total_tuples ) ; //Create temp's tuples
	int temp_counter = 0; //We keep a counter so we know where we left it from each psum cell
	int curr_sigb = 0; //This is the byte that each psum cell has the frequency for
	for ( int i = 0 ; i < psum_size ; i++ ) { //Fill temp
		curr_sigb = psum[i][0];
		temp_counter = extract_and_add_to_temp ( rel , temp , bpos , temp_counter , curr_sigb ) ;
	}
	//Check if temp_counter == total_tuples
	printf("%d\n",temp_counter);
	if ( temp_counter != total_tuples ) {
		printf("ERROR (sort_join.c line 57): temp_counter not equal to total_tuples \n");
	}
	//Now we have temp ready and we copy it to the original relation
	copy_from_temp ( rel , temp , start , temp_counter ) ;

}

//Copy from our temp relation to our original relation starting from start

void copy_from_temp ( relation *rel , relation *temp , int start , int temp_counter ) {
	int copy_counter = 0 ;
	for (int i = start ; i < start + temp_counter ; i++ ){
		uint64_t key = relation_getkey( temp , copy_counter );
		uint64_t payload = relation_getpayload( temp , copy_counter );
		//Now copy to rel
		relation_setkey ( rel , i , key );
		relation_setpayload ( rel , i , payload );
		copy_counter++;
	}
}

//Search our original relation.For each tuple ,if the key matches with byte then add it to temp

int extract_and_add_to_temp ( relation *rel , relation *temp , int bpos , int temp_counter , int byte ){
	int r_total_tuples = relation_getnumtuples ( rel );
	uint64_t key,payload;
	for (int i = 0; i < r_total_tuples ; i++ ){ //Scan original rel's tuples
		//Get key
		key = relation_getkey ( rel , i /*position of tuple that we want to get*/);
		if ( get_sigbyte ( key , bpos ) == byte ) { //Check if it matches current significant byte
			payload = relation_getpayload ( rel , i ) ; //if yes take payload
			//Then set the values to temp
			relation_setkey( temp, temp_counter , key );
			relation_setpayload( temp , temp_counter , payload );
			temp_counter++;
		}
	}
	return temp_counter;
}

//Fill psum according to given hist

void fill_psum ( int **psum , int *hist , int psum_size ) {
	int i = 0; //idenitifier for psum array
	int carry = 0; //carries the hist value of the last checked so we can add it to the next
	for ( int h = 0 ; h < 256 ; h++ ) {
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
	s_byte = s_byte >> 7 * 8 ;
	return s_byte;
}

//Calculate size (bytes) of sub-relation

int calculate_size ( int total_tuples ) {
	int tuple_size = 128 ;
	int total_tuple_size = total_tuples * tuple_size ;
	return total_tuple_size ;
}

//Count total tuples

int count_tuples ( int start , int end ) { 
	/*  EXAMPLE : WHOLE PART <-- 60 tuples
		then start = 0 and end = 59
		so total_tuples = end - start + 1 ;
	*/
	int total_tuples = end - start + 1 ;
	return total_tuples;
}