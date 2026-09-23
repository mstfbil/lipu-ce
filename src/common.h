#ifndef __COMMON_H__
#define __COMMON_H__

#ifndef VERSION_NO
#define VERSION_NO "v0.0"
#endif

#define BYTES_PER_GLYPH 18
#define GLYPH_SIZE 12
#define GLYPH_COLOR 0

#include <string.h>
#include <graphx.h>
#include <ti/getcsc.h>
#include "states.h"
#include "dictionary_data.h"
#include "bitmap_glyphs.h"

extern int selected_word;

void draw_bitmap_sprite_noclip(const uint8_t sprite[BYTES_PER_GLYPH], int x, int y, uint8_t scale_x, uint8_t scale_y);
void print_string_xy_wrapped(const char *str, int x, int y, int max_width, int line_height);
void print_word_category(word_category_t category);
void go_to_word(int new_word_index);
const char *get_definition(const word_entry_t *entry);

#endif // __COMMON_H__