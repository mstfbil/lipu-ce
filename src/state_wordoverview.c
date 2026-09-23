#include "state_wordoverview.h"
#include "state_wordlist.h"

static void redraw(void)
{
    word_entry_t current_entry = g_dictionary.words[selected_word];

    gfx_SetDraw(gfx_buffer);
    gfx_FillScreen(0xFF);

    // draw top bar
    gfx_SetColor(0x4A);
    gfx_FillRectangle_NoClip(0, 0, GFX_LCD_WIDTH, 20);
    gfx_SetTextFGColor(0xFF);
    gfx_PrintStringXY("lipu CE", 5, 5);
    // selected word idx
    gfx_PrintString(" - ");
    gfx_PrintUInt(selected_word + 1, 1);
    gfx_PrintString("/");
    gfx_PrintUInt(g_dictionary.word_count, 1);

    // draw word sitelen pona glyph
    draw_bitmap_sprite_noclip(bitmap_glyphs[current_entry.sp_glyph_id], 136, 30, 4, 4);

    // word in sitelen Lasina
    gfx_SetTextScale(2, 2);
    gfx_SetTextConfig(gfx_text_noclip);
    int str_width = gfx_GetStringWidth(current_entry.word);
    gfx_SetTextFGColor(0x00);
    gfx_PrintStringXY(current_entry.word, (GFX_LCD_WIDTH - str_width) / 2, 80);

    // word category
    gfx_SetTextScale(1, 1); // reset text scale
    gfx_SetTextXY(5, 100);
    print_word_category(current_entry.category);

    gfx_SetTextConfig(gfx_text_clip);

    // definition
    gfx_SetTextFGColor(0x00);
    print_string_xy_wrapped(get_definition(&current_entry), 5, 120, GFX_LCD_WIDTH - 10, 10);

    gfx_Blit(gfx_buffer);
}

static void init()
{
    redraw();
}

static void step()
{
    static uint8_t pressed_key = 0;
    if ((pressed_key = os_GetCSC()))
    {
        switch (pressed_key)
        {
        case sk_Clear:
            states_EnterState(&STATE_WORDLIST);
            break;
        case sk_Down:
            go_to_word(selected_word + 1);
            redraw();
            break;
        case sk_Up:
            go_to_word(selected_word - 1);
            redraw();
            break;
        }
    }
}

const game_state_t STATE_WORDOVERVIEW = {init, step, NULL, NULL};
