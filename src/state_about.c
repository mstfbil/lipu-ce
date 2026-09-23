#include "state_about.h"
#include "state_wordlist.h"

char *credits_text = "lipu CE " VERSION_NO " - a toki pona dictionary for the TI-84 Plus CE\n\n"
                     "- 2026 (c) Mustafa Bildirici - voltie.is-a.dev\n"
                     "- jan Milon - Mirka1405 on GitHub\n\n"
                     "This project is licensed under the MIT License.\n"
                     "Dictionary data is sourced from lipu-linku/sona and licensed under CC-BY-SA-4.0 license.\n"
                     "Fairfax font is licensed under SIL Open Font License 1.1.\n\n"
                     "Press any key to exit.";

static void draw(void)
{
    gfx_SetDraw(gfx_buffer);
    gfx_FillScreen(0xFF);

    // draw top bar
    gfx_SetColor(0x4A);
    gfx_FillRectangle_NoClip(0, 0, GFX_LCD_WIDTH, 20);
    gfx_SetTextFGColor(0xFF);
    gfx_PrintStringXY("lipu CE", 5, 5);

    gfx_SetTextFGColor(0x00);
    print_string_xy_wrapped(credits_text, 10, 30, GFX_LCD_WIDTH - 20, 10);

    gfx_Blit(gfx_buffer);
}

static void init(void)
{
    draw();
}

static void step(void)
{
    if (os_GetCSC())
        states_EnterState(&STATE_WORDLIST);
}

const game_state_t STATE_ABOUT = {init, step, NULL, NULL};