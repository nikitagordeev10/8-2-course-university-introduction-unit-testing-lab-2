#ifndef EQTEST_H
#define EQTEST_H

#include <gtest/gtest.h>
#include <gmock/gmock-matchers.h>
#include <iostream>
#include <fstream>

extern "C"{
#include "text/text.h"
#include "text/_text.h"
#include "common.h"
}


//TEST(ShowunderscoresTest, string_matching) {
//    // Сравниваемые строки
//    char str1[]="12345";
//    char str2[]="12305";
//    int flag = 0;

//    char a[] = showunderscores("asdf");

//    // Сравниваем две строки
//    if (strcmp (str1, str2)==0)
//       flag = 0;
//    else
//       flag = 1;

//    EXPECT_EQ(flag, 0);
//}

// load.c
// Негативный тест
TEST(load, no_file) {
    text new_txt = create_text();
    std::string output;
    testing::internal::CaptureStdout();
    load(new_txt, "i.txt");
    output = testing::internal::GetCapturedStdout();

    ASSERT_EQ(output, "The file i.txt cannot be opened\n");
}

// Позитивный тест
TEST(TEST_load, suite1)
{
    text txt = create_text();
    char *filename = INPUTDIR "/input.txt";
    load(txt, filename);

    std::ifstream f;
    std::string output;
    node *current = txt->begin;

    EXPECT_NE(txt->begin, nullptr);
    EXPECT_NE(txt->end, nullptr);

    while (std::getline(f, output))
    {
        EXPECT_EQ(current->contents, output);
        current = current->next;
    }
    remove_all(txt);
}

// move.c
TEST(TEST_move_cursor, sute1)
{
    text txt = create_text();
    char *filename = INPUTDIR "/input.txt";
    load(txt, filename);
    move(txt, 2, 3);
    EXPECT_EQ(txt->cursor->position, 3);
    int k = 1;
    node *current = txt->begin;
    while(current != txt->cursor->line)
    {
        k++;
        current = current->next;
    }
    EXPECT_EQ(k, 2);
    remove_all(txt);
}

TEST(Test_m, cannot_m) {
    text txt = create_text();
    char *filename = INPUTDIR "/input.txt";
    load(txt, filename);

    std::string output;
    move(txt, 0, 10);
    output = testing::internal::GetCapturedStdout();

    ASSERT_EQ(output, "hellddo|\nworld\n");
    remove_all(txt);
}

TEST(TEST_cursuo, test_mistake_line_argument_large)
{
    /*
     * Тест перемещения курсора.
     * Негативный тест.
     * Попытка поставить курсор в несуществующую строку (слишком большую).
     */

    text txt = create_text();
    append_line(txt, "Example text in line 1.");
    append_line(txt, "Example text in line 2.");
    append_line(txt, "Example text in line 3.");
    move(txt, 100, 0);
    EXPECT_EQ(txt->cursor->position, 0);
    int k = 1;
    node *current = txt->begin;
    while(current != txt->cursor->line)
    {
        k++;
        current = current->next;
    }
    EXPECT_EQ(k, txt->cursor->position);
    remove_all(txt);
}

// mpweb.c
// remove_next.c
// save.c
// show.c
// showunderscores.c
// append_line.c
// create_text.c
// process_forward.c


#endif // EQTEST_H
