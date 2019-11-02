#include "list.h"


Listnode* initListNode(List *list)
{
	Listnode *new_node = malloc(sizeof(Listnode));
	new_node->tuples = malloc(sizeof(Tuple) * list->tuples_size);
	new_node->current_position = 0;
	new_node->next = NULL;
	return new_node;
}





void initlist(List *list, int maxbytes, int record_size)
{
	list->head= NULL;
	list->tail = NULL;
	list->counter = 0;
	list->tuples_size = (maxbytes/record_size);
}


int isEmpty(List *list)
{
	return list->counter == 0;
}


void insertNewNode(List *list)
{
	Listnode *new_node = initListNode(list);
	if(isEmpty(list))
	{
		list->counter = 1;
		list->head = new_node;
		list->tail = new_node;
		return;
	}
	list->counter++;
	list->tail->next = new_node;
	list->tail = new_node;
}

void insertElement(List *list, Tuple tuple1, Tuple tuple2)
{
	if(isEmpty(list))
	{
		insertNewNode(list);
	}
	if(list->tuples_size == list->tail->current_position)//an xoraei kainourgio record ston komvo tis listas
	{
		insertNewNode(list);
	}
	list->tail->tuples[list->tail->current_position].key = tuple1.payload;
	list->tail->tuples[list->tail->current_position].payload = tuple2.payload;
	list->tail->current_position++;

}

void join(relation *relR, relation *relS, List *list){
	
	int i, k = 0;
	int prevk = 0;

	for(i = 0; i<relR->num_tuples; i++) //i<relR->num_tuples
	{
		if (i > 0 && relR->tuples[i].key == relR->tuples[i-1].key)
		{
			k = prevk;
		}else{
			prevk = k;
	    }

		if(k == relS->num_tuples) break;

		if(isEqual(relR, relS, i, k))
		{
			while (isEqual(relR, relS, i, k))
			{
				insertElement(list, relR->tuples[i], relS->tuples[k]);
				k++;
			}
		}else
		{
			for( int64_t j = relS->tuples[k].payload; j < relS->num_tuples; j++)
			{
				if(isEqual(relR, relS, i, j)) insertElement(list, relR->tuples[i], relS->tuples[j]);
			}
		}	
	}
    printList(list);
}

int isEqual(relation *relR, relation *relS, int i, int k)
{
	return relR->tuples[i].key == relS->tuples[k].key;
}

void printList(List *list)
{
	Listnode *tmp = list->head;
	while(tmp != NULL)
	{
		printTuples(tmp);
		tmp = tmp->next;
	}
	printf("\n\n");
}

void printTuples(Listnode *node)
{
	int i;
	for(i=0;i<node->current_position;i++)
		printf("(%ld, %ld)\t", node->tuples[i].key, node->tuples[i].payload);
}


void freeListNode(Listnode *listnode)
{
	free(listnode->tuples);
}

void freeList(List *list)
{
	Listnode *tmp;
	while(list->head != NULL)
	{
		tmp = list->head;
		list->head = list->head->next;
		freeListNode(tmp);
		free(tmp);
	}
}


relation getRelation(relation rel){
	uint64_t r = 0;
	for (int i=0; i<10; i++)
	{
		r = r*2 + rand()%2;
		rel.tuples[i].key = r;
		rel.tuples[i].payload = i;
		rel.num_tuples++;
	}
	return rel;
}

relation getRelationR(relation R)
{
	int rowid = 0;
    char *token;
    char help[100000];
    FILE *df;
    R.tuples = malloc(sizeof(Tuple) * 1000); //*num_tuples
    df = fopen("Rdata.txt", "r");
    fscanf(df ,"%s", help);
    token = strtok(help, ",");
    int i = 0; int n = 0;
    while (token != NULL)
    { 
        R.tuples[i].key = atoi(token);
        R.tuples[i].payload = rowid;
        token = strtok (NULL, ",");
        i++;
        rowid++;
        R.num_tuples++;
    }
    n = i;
    return R;
}

relation getRelationS(relation S)
{
	int rowid = 0;
    char *token;
    char help[10000];
    FILE *df;
    S.tuples = malloc(sizeof(Tuple) * 1000); //*num_tuples
    df = fopen("Sdata.txt", "r");
    fscanf(df ,"%s", help);
    token = strtok(help, ",");
    int i = 0; int n = 0;
    while (token != NULL)
    { 
        S.tuples[i].key = atoi(token); 
        S.tuples[i].payload = rowid;
        token = strtok (NULL, " , ");
        i++;
        rowid++;
        S.num_tuples++;
    }
    n = i;
    return S;

} 

void printRelation(relation rel)
{
    for (int i=0; i<rel.num_tuples; i++)
    {

        printf("%ld ", rel.tuples[i].payload);
        printf("%ld\t", rel.tuples[i].key);
    }
    printf("\n\n");
}


















