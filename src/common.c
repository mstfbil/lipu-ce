#include "common.h"

int selected_word = 0;

void draw_bitmap_sprite_noclip(const uint8_t sprite[BYTES_PER_GLYPH], int x, int y, uint8_t scale_x, uint8_t scale_y)
{
    /* how this works:
    we start with a mask of 10000000
    we shift it right by one position and use it to get a bit out of a byte
    when the mask is 0; this means that we are done with this byte and move on to the next
    */
    uint8_t mask = 0b10000000;
    uint8_t sprite_index = 0;
    gfx_SetColor(GLYPH_COLOR);
    for (uint8_t row = 0; row < GLYPH_SIZE; row++)
    {
        uint8_t run_len = 0;
        for (uint8_t col = 0; col < GLYPH_SIZE; col++)
        {
            if (mask == 0)
            {
                mask = 0b10000000;
                sprite_index++;
            }
            if (sprite[sprite_index] & mask)
                run_len++;
            else
            {
                gfx_FillRectangle_NoClip(
                    x + (col - run_len) * scale_x,
                    y + row * scale_y,
                    run_len * scale_x,
                    scale_y);
                run_len = 0;
            }
            mask >>= 1;
        }
        if (run_len)
            gfx_FillRectangle_NoClip(
                x + (GLYPH_SIZE - run_len) * scale_x,
                y + row * scale_y,
                run_len * scale_x,
                scale_y);
    }
}

void print_string_xy_wrapped(const char *str, int x, int y, int max_width, int line_height)
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

void print_word_category(word_category_t category)
{
    switch (category)
    {
    case CORE:
        gfx_SetTextBGColor(0x86);
        gfx_PrintString("core");
        break;
    case COMMON:
        gfx_SetTextBGColor(0x9D);
        gfx_PrintString("common");
        break;
    case UNCOMMON:
        gfx_SetTextBGColor(0xE5);
        gfx_PrintString("uncommon");
        break;
    case OBSCURE:
        gfx_SetTextBGColor(0xFB);
        gfx_PrintString("obscure");
        break;
    }
    gfx_SetTextBGColor(0xE0);
}

void go_to_word(int new_word_index)
{
    if (new_word_index >= g_dictionary.word_count)
        selected_word = 0;
    else if (new_word_index < 0)
        selected_word = g_dictionary.word_count - 1;
    else
        selected_word = new_word_index;
}

const char *get_definition(const word_entry_t *entry)
{
    if (!entry)
        return NULL;
    return g_dictionary.def_string_table + entry->def_offset;
}