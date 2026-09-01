#ifndef __BITMAP_GLYPHS_H__
#define __BITMAP_GLYPHS_H__

#define GLYPH_WIDTH 12
#define GLYPH_HEIGHT 12
#define BYTES_PER_IMAGE (GLYPH_WIDTH * GLYPH_HEIGHT / 8)

extern const unsigned char bitmap_glyphs[][BYTES_PER_IMAGE];
#define BITMAP_GLYPHS_LEN (sizeof(bitmap_glyphs) / sizeof(bitmap_glyphs[0]))

#endif // __BITMAP_GLYPHS_H__
