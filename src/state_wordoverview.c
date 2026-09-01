#include "state_wordoverview.h"
#include "state_wordlist.h"

static word_entry_t current_entry;

static void redraw(void);

void state_WordOverview_SetEntry(const uint16_t word_idx)
{
    current_entry = g_dictionary.words[word_idx];
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
        default:
            break;
        }
    }
}

static void redraw(void)
{
    gfx_SetDraw(gfx_buffer);
    gfx_FillScreen(0xFF);

    // draw top bar
    gfx_SetColor(0x4A);
    gfx_FillRectangle_NoClip(0, 0, GFX_LCD_WIDTH, 20);
    gfx_SetTextFGColor(0xFF);
    gfx_PrintStringXY("lipu CE", 5, 5);

    // draw word sitelen pona glyph
    drawBitmapSprite_NoClip(bitmap_glyphs[current_entry.sp_glyph_id], 136, 30, 4, 4);

    // word in sitelen Lasina
    gfx_SetTextScale(2, 2);
    gfx_SetTextConfig(gfx_text_noclip);
    const int word_width = gfx_GetStringWidth(current_entry.word);
    gfx_SetTextFGColor(0x00);
    gfx_PrintStringXY(current_entry.word, (GFX_LCD_WIDTH - word_width) / 2, 80);
    gfx_SetTextScale(1, 1); // reset text scale
    gfx_SetTextConfig(gfx_text_clip);

    // definition
    gfx_PrintStringXYWrapped(getDefinition(&current_entry), 5, 100, GFX_LCD_WIDTH - 10, 10);

    gfx_Blit(gfx_buffer);
}

const game_state_t STATE_WORDOVERVIEW = {init, step, NULL, NULL};
