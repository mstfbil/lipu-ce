#include "common.h"
// A glyph is 12x12 in size, so this format uses 144 bits, or 18 bytes.
// BYTES_PER_GLYPH is defined in common.h
#define GLYPH_SIZE 12
#define GLYPH_COLOR 0 // black if default palette is unchanged

void drawBitmapSprite_NoClip(const uint8_t sprite[BYTES_PER_GLYPH], int x, int y, uint8_t scale_x, uint8_t scale_y){
    /* how this works:
    we start with a mask of 10000000
    we shift it right by one position and use it to get a bit out of a byte
    when the mask is 0; this means that we are done with this byte and move on to the next
    */
    uint8_t mask = 0b10000000;
    uint8_t sprite_index = 0;
    gfx_SetColor(GLYPH_COLOR);
    for(uint8_t row=0;row<GLYPH_SIZE;row++){
        uint8_t run_len = 0;
        for(uint8_t col=0;col<GLYPH_SIZE;col++){
            if(mask==0){mask=0b10000000;sprite_index++;}
            if(sprite[sprite_index]&mask)run_len++;
            else {
                gfx_FillRectangle_NoClip(
                    x + (col-run_len)*scale_x,
                    y + row*scale_y,
                    run_len*scale_x,
                    scale_y);
                run_len=0;
                }
            mask>>=1;
        }
        if(run_len)
            gfx_FillRectangle_NoClip(
                x + (GLYPH_SIZE-run_len)*scale_x,
                y + row*scale_y,
                run_len*scale_x,
                scale_y);
    }
}

void gfx_PrintStringXYWrapped(const char *str, int x, int y, int max_width, int line_height)
{
    gfx_SetTextXY(x, y);
    const char *word_start = str;
    const char *cursor = str;

    while (*cursor)
    {
        if (*cursor == ' ' || *cursor == '\n' || *(cursor + 1) == '\0')
        {
            size_t word_len = cursor - word_start;
            if (*(cursor + 1) == '\0' && *cursor != ' ' && *cursor != '\n')
            {
                word_len++;
            }

            char word_buf[64];
            if (word_len >= sizeof(word_buf))
                word_len = sizeof(word_buf) - 1;
            strncpy(word_buf, word_start, word_len);
            word_buf[word_len] = '\0';

            int word_width = gfx_GetStringWidth(word_buf);
            int space_width = gfx_GetCharWidth(' ');

            if (gfx_GetTextX() + word_width > x + max_width && gfx_GetTextX() > x)
                gfx_SetTextXY(x, gfx_GetTextY() + line_height);

            gfx_PrintString(word_buf);

            if (*cursor == ' ')
            {
                gfx_SetTextXY(gfx_GetTextX() + space_width, gfx_GetTextY());
            }
            else if (*cursor == '\n')
            {
                gfx_SetTextXY(x, gfx_GetTextY() + line_height);
            }

            word_start = cursor + 1;
        }
        cursor++;
    }
}

const char *getDefinition(const word_entry_t *entry)
{
    if (!entry)
        return NULL;
    return g_dictionary.def_string_table + entry->def_offset;
}