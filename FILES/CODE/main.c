#include "main.h"



int main()
{
	List list;
	relation R, S;

	initlist(&list, MAXSIZE, sizeof(Tuple));


	R.tuples = malloc(sizeof(Tuple) * 1000);
	S.tuples = malloc(sizeof(Tuple) * 1000);
	R.num_tuples = 0;
	S.num_tuples = 0;

	R = getRelationR(R);
	S = getRelationS(S);

	printf("Relation R elements are :\n\n");
	printRelation(R);
	printf("Relation S elements are :\n\n");
	printRelation(S);

	join(&R, &S, &list);
	printf("The list created to hold the results contains %d equal relations divided into %d nodes.\n", ((list.tuples_size * --list.counter) + list.tail->current_position), list.counter);
	printf("Each node contains %d relations\n\n", list.tuples_size);

}