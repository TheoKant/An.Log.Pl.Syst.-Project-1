#ifndef UNITEST_H
#define UNITEST_H

#include "CuTest.h"

CuSuite* EqualUtilGetSuite();

void TestJoin(CuTest *tc);

void RunAllTest(void);

#endif
