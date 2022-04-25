#include "text/text.h"
#include "common.h"
#include <stdio.h>

void write_line(int index, char *contents, int cursor, void *data) {
    UNUSED(index);
    UNUSED(cursor);
    FILE* file = data;
    fprintf(file, "%s", contents);
}

void save(text txt, char *filename) {
    FILE* file = fopen(filename, "w");
    if (!file) {
        printf("The file %s cannot be opened\n", filename);
        return;
    }
    process_forward(txt, write_line, file);
}
