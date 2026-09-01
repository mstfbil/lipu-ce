#ifndef __COMMON_H__
#define __COMMON_H__

#define BYTES_PER_GLYPH 18

#include <string.h>
#include <graphx.h>
#include <ti/getcsc.h>
#include "states.h"
#include "dictionary_data.h"

#include "bitmap/gen_bitmap_glyphs.h"

extern void drawBitmapSprite_NoClip(const uint8_t sprite[BYTES_PER_GLYPH], int x, int y, uint8_t scale_x, uint8_t scale_y);

#ifndef VERSION_NO
#define VERSION_NO "v0.0"
#endif

void gfx_PrintStringXYWrapped(const char *str, int x, int y, int max_width, int line_height);
const char *getDefinition(const word_entry_t *entry);

#endif // __COMMON_H__