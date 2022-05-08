#ifndef EQTEST_H
#define EQTEST_H
#include <gtest/gtest.h>
#include <gmock/gmock-matchers.h>
#include <string>
#include <fstream>

extern "C" {
    #include <text.h>
    #include "../editor/common.h"
}

TEST(ShowUnderscoresTest, showunderscores) {
    ASSERT_EQ(showunderscores(/tests/input/loremd.txt), lorem_ipsum);
}
