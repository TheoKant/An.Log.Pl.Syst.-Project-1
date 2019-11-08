#ifndef UNITEST_H
#define UNITEST_H

#include "../HEADERS/CuTest.h"
#include "../HEADERS/list.h"

CuSuite* EqualUtilGetSuite();

void TestJoin(CuTest *tc);

void RunAllTest(void);

#endif
