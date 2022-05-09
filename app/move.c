/**
 * move.c - команду перемещения в заданную позициюа
 *
 * Copyright (c) 2022, Nikita Gordeev <gordeev@petrsu.ru>
 *
 * This code is licensed under a MIT-style license.
 */

#include <stdio.h>
#include "common.h"
#include "text/_text.h"
#include "text/text.h"

void move(text txt, int line, int col) {
    int k = 1;
    node *current = txt->begin;
    if (col >= 0) {
        txt->cursor->position = col;
    } else {
        txt->cursor->position = 0;
    }

    if (line > 0) {
        int l = txt->length;
        if (line > l)
            line = l;

        while(current) {
            if (k == line) {
                txt->cursor->line = current;
                break;
            }
            current = current->next;
            k ++;
        }
    }
    else {
        txt->cursor->line = current;
    }
}
