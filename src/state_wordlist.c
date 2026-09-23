#include "state_wordlist.h"
#include "state_wordoverview.h"
#include "state_about.h"

#define WORD_LIST_START_Y 25
#define WORD_BOX_HEIGHT 40
#define BOX_MARGIN 5
#define MAX_WORDS_SHOWN 5

static uint8_t ALPHABET_KEY_LOOKUP[TOKI_PONA_ALPHABET_SIZE] = {sk_Math, sk_Sin, sk_Square, sk_Comma, sk_LParen, sk_RParen, sk_Div, sk_Log, sk_7, sk_8, sk_Ln, sk_4, sk_5, sk_Sub};

static int wordlist_start_idx = 0;

static void DrawWordInfoBox(const word_entry_t *entry, int y, bool selected)
{
    // box
    if (selected)
    {
        gfx_SetColor(0x4A);
        gfx_Rectangle(BOX_MARGIN, y + BOX_MARGIN, GFX_LCD_WIDTH - BOX_MARGIN * 2, WORD_BOX_HEIGHT - BOX_MARGIN);
        gfx_Rectangle(BOX_MARGIN - 3, y + BOX_MARGIN - 3, GFX_LCD_WIDTH - (BOX_MARGIN - 3) * 2, WORD_BOX_HEIGHT - (BOX_MARGIN - 6));
    }
    else
    {
        gfx_SetColor(0xB5);
        gfx_Rectangle(BOX_MARGIN, y + BOX_MARGIN, GFX_LCD_WIDTH - BOX_MARGIN * 2, WORD_BOX_HEIGHT - BOX_MARGIN);
    }

    // sitelen pona
    drawBitmapSprite_NoClip(bitmap_glyphs[entry->sp_glyph_id], 10, y + 12, 2, 2);

    // sitelen Lasina
    gfx_SetTextFGColor(0x00);
    gfx_SetTextXY(40, y + 19);
    gfx_PrintString(entry->word);
    gfx_PrintString(" ");

    // word category
    PrintWordCategory(entry->category);

    gfx_SetTextFGColor(0xB5);
    gfx_PrintString(" - ");
    gfx_SetClipRegion(0, 0, GFX_LCD_WIDTH - 2 * BOX_MARGIN, GFX_LCD_HEIGHT);
    gfx_PrintString(getDefinition(entry));
    gfx_SetClipRegion(0, 0, GFX_LCD_WIDTH, GFX_LCD_HEIGHT);
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
    // selected word idx
    gfx_PrintString(" - ");
    gfx_PrintUInt(selected_word + 1, 1);
    gfx_PrintString("/");
    gfx_PrintUInt(g_dictionary.word_count, 1);
    // about menu tip
    gfx_PrintString(" - [mode] About menu");

    // draw word list
    gfx_SetTextConfig(gfx_text_clip);
    for (int i = 0; i < 5; i++)
    {
        int y = WORD_LIST_START_Y + (WORD_BOX_HEIGHT + 2) * i;
        DrawWordInfoBox(&g_dictionary.words[wordlist_start_idx + i], y, wordlist_start_idx + i == selected_word);
    }

    gfx_Blit(gfx_buffer);
}

static void ScrollList(void)
{
    if (selected_word >= wordlist_start_idx + MAX_WORDS_SHOWN)
        wordlist_start_idx = selected_word - MAX_WORDS_SHOWN + 1;
    if (selected_word < wordlist_start_idx)
        wordlist_start_idx = selected_word;
}

static void jumpToLetter(uint8_t key)
{
    for (int i = 0; i < TOKI_PONA_ALPHABET_SIZE; i++)
        if (key == ALPHABET_KEY_LOOKUP[i])
        {
            int new_idx = g_dictionary.letter_index[i];

            GoToWord(new_idx);
            ScrollList();
            redraw();
        }
}

static void init(void)
{
    ScrollList();
    redraw();
}

static void step(void)
{
    static uint8_t pressed_key = 0;
    if ((pressed_key = os_GetCSC()))
    {
        switch (pressed_key)
        {
        case sk_Clear:
            states_EnterState(NULL);
            break;
        case sk_Mode:
            states_EnterState(&STATE_ABOUT);
            break;
        case sk_Down:
            GoToWord(selected_word + 1);
            ScrollList();
            redraw();
            break;
        case sk_Up:
            GoToWord(selected_word - 1);
            ScrollList();
            redraw();
            break;
        case sk_Enter:
            states_EnterState(&STATE_WORDOVERVIEW);
            break;
        default:
            jumpToLetter(pressed_key);
            break;
        }
    }
}

const game_state_t STATE_WORDLIST = {init, step, NULL, NULL};