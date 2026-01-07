#include "ascii.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

AsciiArt load_ascii(const char *path) {
    AsciiArt art = {0};
    FILE *fp = fopen(path, "r");
    if (!fp) return art;

    char buf[512];
    while (fgets(buf, sizeof(buf), fp)) art.line_count++;
    rewind(fp);

    art.lines = malloc(sizeof(char*) * art.line_count);

    for (int i = 0; i < art.line_count; i++) {
        fgets(buf, sizeof(buf), fp);
        buf[strcspn(buf, "\n")] = '\0';
        int len = strlen(buf);

        if (len > art.max_width) art.max_width = len;

        art.lines[i] = malloc(len + 1);
        strcpy(art.lines[i], buf);
    }
    fclose(fp);
    return art;
}

void free_ascii(AsciiArt *art) {
    for (int i = 0; i < art->line_count; i++) {
        free(art->lines[i]);
    }
    free(art->lines);
}
