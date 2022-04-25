#include "_text.h"
#include "text.h"

void move_crsr(text txt, int line, int col) {
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
