/**
 * move.c - команду перемещения в заданную позициюа
 *
 * Copyright (c) 2022, Nikita Gordeev <gordeev@petrsu.ru>
 *
 * This code is licensed under a MIT-style license.
 */

#include "_text.h"
#include "text.h"

void move(text txt, int line, int col) {
    node *current = txt->begin;
    int index = 0;
    while (current) {
        if (index == line) break;
        current = current->next;
        index++;
    }
    txt->cursor->line = current;
    txt->cursor->position = col;
}
