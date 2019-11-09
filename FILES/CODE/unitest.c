#include "../HEADERS/unitest.h"
#include "../HEADERS/list.h"

void TestJoin(CuTest *tc)
{
	relation input1;
	input1.tuples = malloc(sizeof(tuple));
	input1.tuples[1].key = 3;

	relation input2;
	input2.tuples = malloc(sizeof(tuple));
	input2.tuples[2].key = 2;

	int actual = isEqual(&input1, &input2, 1, 2);
	int expected = 1;

	CuAssertIntEquals(tc, expected, actual);
}

CuSuite* EqualUtilGetSuite()
{
	CuSuite* suite = CuSuiteNew();
    SUITE_ADD_TEST(suite, TestJoin);
    return suite;
}


void RunAllTest(void)
{
	CuString *output = CuStringNew();
    CuSuite* suite = CuSuiteNew();
        
    CuSuiteAddSuite(suite, EqualUtilGetSuite());
    
    CuSuiteRun(suite);
    CuSuiteSummary(suite, output);
    CuSuiteDetails(suite, output);

    FILE *fp;
    fp = fopen("UnityTest.txt", "w");
    fprintf(fp, "%s\n", output->buffer);
    fclose(fp); //Don't forget to close the file when finished

 
}

