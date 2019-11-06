#include "../HEADERS/main.h"



// Function rec_sort used to sort the array

void rec_sort ( relation * /*relation*/ , int /*start*/ , int /*end*/ , int /*significant byte no*/ ) ;

//Calculate size (bytes) of sub-relation

int calculate_size ( int /*start*/ , int /*end*/ ) ;

//Create Hist

int *create_hist ( relation * , int * , int , int , int ) ;

//Funtction print_array

void print_array ( int ** /*array*/ , int /*size of array*/ ) ;

//Returns i significant byte of the key

uint64_t get_sigbyte ( uint64_t , int ) ;

//Returns requiered size for the psum

int get_psumsize ( int * ) ;

//Fill psum according to given hist

void fill_psum ( int ** , int * , int ) ;