#include "Types.hpp"
#include <iostream>

struct UnitTest {
    static void test() {

    }
};

#define ASSERT(CONDITION, MESSAGE) \
    UnitTest::test(CONDITION, #CONDITION MESSAGE)

