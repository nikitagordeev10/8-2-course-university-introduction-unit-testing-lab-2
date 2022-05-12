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

char *input = INPUTDIR "/input.txt";
char *no_spaces_input = INPUTDIR "/no_spaces_input.txt";
char *unusual_spaces_input = INPUTDIR "/unusual_spaces_input.txt";

/* ------------------- move.c -------------------  */

/* Позитивный тест */
TEST(TestMove, within_text)
{
    text txt = create_text();
    load(txt, input);
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
    load(txt, input);
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
    load(txt, input);
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
    load(txt, input);
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
    load(txt, input);
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
    load(txt, input);
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
    load(new_txt, input);
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
    load(txt, input);

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

TEST(TestShow, last_line_in_text)
{
    text txt = create_text();
    load(txt, input);
    testing::internal::CaptureStdout();
    show(txt);
    std::string output = testing::internal::GetCapturedStdout();
    int i = 0;
    node *current = txt->begin;
    while(current)
    {
        for (int j = 0; j < strlen(current->contents); j++)
        {
            EXPECT_EQ(output[i], current->contents[j]);
            i++;
        }
        if (current != txt->end)
            i++;
        current = current->next;
    }
    EXPECT_EQ(output[i], '|');
    remove_all(txt);
}

TEST(TestShow, second_line_in_text)
{
    text txt = create_text();
    load(txt, input);
    move(txt, 74, 2);
    testing::internal::CaptureStdout();
    show(txt);
    std::string output = testing::internal::GetCapturedStdout();
    int i = 0;
    node *current = txt->begin;
    while(current)
    {
        for (int j = 0; j < strlen(current->contents); j++)
        {
            if (current == txt->cursor->line
                   && j == txt->cursor->position)
            {
                EXPECT_EQ(output[i], '|');
                i++;
            }
            EXPECT_EQ(output[i], current->contents[j]);
            i++;
        }
        i++;
        current = current->next;
    }
    remove_all(txt);
}

TEST(TestShow, no_text)
{
    text txt = create_text();
    testing::internal::CaptureStderr();
    show(txt);
    std::string output = testing::internal::GetCapturedStderr();
    EXPECT_EQ(output, "There are already no any lines in the text!\n");

    remove_all(txt);
}

/* ------------------- showunderscores.c -------------------  */

TEST(TestShowunderscores, real_file)
{
    text txt = create_text();
    load(txt, input);

    testing::internal::CaptureStdout();
    showunderscores(txt);
    std::string output = testing::internal::GetCapturedStdout();

    // читаем ожидаемые строки из файла input.txt
    char *filename = (char *)malloc(sizeof(char) * 1024);
    sprintf(filename, "%s/with_spaces_ouput.txt", INPUTDIR);
    std::ifstream f(filename);
    free(filename);
    std::string content;
    content.assign( (std::istreambuf_iterator<char>(f) ),
                    (std::istreambuf_iterator<char>()    ) );
    content[content.length()-1] = '|';
    content += "\n";
    EXPECT_EQ(output, content);
    remove_all(txt);
}

TEST(TestShowunderscores, without_spaces)
{
    text txt = create_text();
    load(txt, no_spaces_input);

    testing::internal::CaptureStdout();
    showunderscores(txt);
    std::string output = testing::internal::GetCapturedStdout();

    // читаем ожидаемые строки из файла input.txt
    char *filename = (char *)malloc(sizeof(char) * 1024);
    sprintf(filename, "%s/no_spaces_output.txt", INPUTDIR);
    std::ifstream f(filename);
    free(filename);
    std::string content;
    content.assign( (std::istreambuf_iterator<char>(f) ),
                    (std::istreambuf_iterator<char>()    ) );
    content[content.length()-1] = '|';
    content += "\n";
    EXPECT_EQ(output, content);
    remove_all(txt);
}

TEST(TestShowunderscores, unusual_spaces)
{
    text txt = create_text();
    load(txt, unusual_spaces_input);

    testing::internal::CaptureStdout();
    showunderscores(txt);
    std::string output = testing::internal::GetCapturedStdout();

    // читаем ожидаемые строки из файла input.txt
    char *filename = (char *)malloc(sizeof(char) * 1024);
    sprintf(filename, "%s/unusual_spaces_output.txt", INPUTDIR);
    std::ifstream f(filename);
    free(filename);
    std::string content;
    content.assign( (std::istreambuf_iterator<char>(f) ),
                    (std::istreambuf_iterator<char>()    ) );
    content[content.length()-1] = '|';
    content += "\n";
    EXPECT_EQ(output, content);
    remove_all(txt);
}

TEST(TestShowunderscores, empty)
{
    text txt = create_text();
    testing::internal::CaptureStderr();
    showunderscores(txt);
    std::string output = testing::internal::GetCapturedStderr();
    EXPECT_EQ(output, "There are already no any lines in the text!\n");

    remove_all(txt);
}

#endif // EQTEST_H
