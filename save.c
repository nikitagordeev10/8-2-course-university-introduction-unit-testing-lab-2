/**
 * save.c -- функция сохранения текста в файл
 * 
 * Copyright (c) 2022, Gordeev Nikita <gordeev@petrsu.ru>
 *
 * This code is licensed under a MIT-style license.
 */
 
#include <stdio.h>
#include "common.h"
#include "text/_text.h"
#include "text/text.h"

/**
 * Сохраняет содержимое указанного файла
 */
 
void save(text txt, char *filename)
{
    FILE *f;

    if (txt == NULL || txt->length == 0)
    {
        fprintf(stderr, "The text doesn't exist\n");	
        return;
    }
    
    /* Открываем файл для чтения, контролируя ошибки */
    if ((f = fopen(filename, "w")) == NULL)
    {
        printf("File %s can't be opened\n", filename);
        return;
    }

    assert(txt->begin != NULL && txt->end != NULL);

    node *current = txt->begin;

    do
    {
        fprintf(f, "%s\n", current->contents);
        current = current->next;
    } while(current);

    fclose (f);
}
