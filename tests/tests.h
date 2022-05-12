#ifndef EQTEST_H
#define EQTEST_H

#include <gtest/gtest.h>
#include <gmock/gmock-matchers.h>
#include <iostream>
#include <fstream>

extern "C"{
#include "text.h"
#include "_text.h"
#include "common.h"
}

/* =================== constants ===================  */

char *input_file = INPUTDIR "/input.txt";

/* ------------------- move.c -------------------  */

/* Позитивный тест */
TEST(TestMove, within_text)
{
    text txt = create_text();
    load(txt, input_file);
    move(txt, 2, 3);

    //позиция в строке
    EXPECT_EQ(txt->cursor->position, 3);

    int line = 1;
    node *current = txt->begin;
    while(current != txt->cursor->line) {
        line++;
        current = current->next;
    }

    //номер строки
    EXPECT_EQ(line, 2);

    remove_all(txt);
}


/* Негативный тест */
TEST(TestMove, outside_text_up)
{
    text txt = create_text();
    load(txt, input_file);
    move(txt, -500, 0);

    //позиция в строке
    EXPECT_EQ(txt->cursor->position, 0);

    int line = 1;
    node *current = txt->begin;
    while(current != txt->cursor->line) {
        line++;
        current = current->next;
    }

    //номер строки
    EXPECT_EQ(line, 1);

    remove_all(txt);
}


/* Негативный тест */
TEST(TestMove, outside_text_down)
{
    text txt = create_text();
    load(txt, input_file);
    move(txt, 500, 0);

    //позиция в строке
    EXPECT_EQ(txt->cursor->position, 0);

    int line = 1;
    node *current = txt->begin;
    while(current != txt->cursor->line) {
        line++;
        current = current->next;
    }

    //номер строки
    EXPECT_EQ(line, txt->length);

    remove_all(txt);
}


/* Негативный тест */
TEST(TestMove, outside_text_left)
{
    text txt = create_text();
    load(txt, input_file);
    move(txt, 1, -5);

    //позиция в строке
    EXPECT_EQ(txt->cursor->position, 0);

    int line = 1;
    node *current = txt->begin;
    while(current != txt->cursor->line) {
        line++;
        current = current->next;
    }

    //номер строки
    EXPECT_EQ(line, 1);

    remove_all(txt);
}


/* Позитивный тест */
TEST(TestMove, outside_text_right)
{
    text txt = create_text();
    load(txt, input_file);
    move(txt, 1, 500000000);

    //позиция в строке
    EXPECT_EQ(txt->cursor->position, 500000000);

    int line = 1;
    node *current = txt->begin;
    while(current != txt->cursor->line) {
        line++;
        current = current->next;
    }

    //номер строки
    EXPECT_EQ(line, 1);

    remove_all(txt);
}

/* Позитивный тест */
TEST(TestMove, zero_coordinates)
{
    text txt = create_text();
    load(txt, input_file);
    move(txt, 0, 0);

    //позиция в строке
    EXPECT_EQ(txt->cursor->position, 0);

    int line = 1;
    node *current = txt->begin;
    while(current != txt->cursor->line) {
        line++;
        current = current->next;
    }

    //номер строки
    EXPECT_EQ(line, 1);

    remove_all(txt);
}

/* ------------------- load.c -------------------  */

/* Позитивный тест */
TEST(TestLoad, existing_file) {
    text new_txt = create_text();
    std::string output;
    testing::internal::CaptureStdout();
    load(new_txt, input_file);
    output = testing::internal::GetCapturedStdout();

    EXPECT_EQ(output, "");
}

/* Негативный тест */
TEST(TestLoad, non_existent_file) {
    text new_txt = create_text();
    std::string output;
    testing::internal::CaptureStdout();
    load(new_txt, "fakefile.txt");
    output = testing::internal::GetCapturedStdout();

    EXPECT_EQ(output, "The file fakefile.txt cannot be opened\n");
}

/* ------------------- mpweb.c -------------------  */

/* Позитивный тест */
TEST(TestMpweb, within_text)
{
    text txt = create_text();
    load(txt, input_file);

    node *current = txt->begin;
    move(txt, 1, 10);
    mpweb(txt);

    int i = 0;
    while(current) {
      i++;
      if (txt->cursor->line == current) {
        break;
      }
      current = current->next;
    }

    EXPECT_EQ(txt->cursor->position, 7);
    EXPECT_EQ(i, 1);

    remove_all(txt);
}

/* ------------------- rn.c -------------------  */

/* ------------------- save.c -------------------  */

TEST (TestSave, default_save)
{
    /*
     * Тест на сохранения файла.
     * Позитивный тест.
     */

    text txt = create_text();
    append_line(txt, "Example text in line.");

    testing::internal::CaptureStdout();
    save(txt, "example_result.txt");
    remove_all(txt);

    std::string output = testing::internal::GetCapturedStdout();
    EXPECT_EQ(output, "Save file successeed!\n");
    remove_all(txt);
}

TEST (TestSave, emply_txt_structure)
{
    /*
     * Тест на сохранения файла.
     * Негативный тест.
     * Передаваемые параметры - пустая структура txt, NULL, пустое имя файла.
     */

    text txt = create_text();

    testing::internal::CaptureStderr();
    save(txt, "test_save.txt");
    save(NULL, "test_save.txt");
    append_line(txt, "Example text.");
    save(txt, NULL);
    save(txt, "");

    std::string output = testing::internal::GetCapturedStderr();
    EXPECT_EQ(output, "The text doesn't exist\nThe text doesn't exist\nFile (null) can't be opened\nFile  can't be opened\n");
    remove_all(txt);
}

/* ------------------- show.c -------------------  */

TEST(TestShow, suite3)
{
    text txt = create_text();
    testing::internal::CaptureStderr();
    show(txt);
    std::string output = testing::internal::GetCapturedStderr();
    EXPECT_EQ(output, "There are already no any lines in the text!\n");

    remove_all(txt);
}

#endif // EQTEST_H
