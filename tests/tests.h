#ifndef EQTEST_H
#define EQTEST_H
#include <gtest/gtest.h>
#include <gmock/gmock-matchers.h>
#include <iostream>

extern "C"{
#include "text/text.h"
#include "text/_text.h"
#include "common.h"
}

TEST(simple_TEST, base)
{
    EXPECT_EQ(1, 1);
}

#endif // EQTEST_H
