#ifndef ASCII_H
#define ASCII_H

typedef struct {
    char **lines;
    int line_count;
    int max_width;
} AsciiArt;

AsciiArt load_ascii(const char *path);
void free_ascii(AsciiArt *art);

#endif
