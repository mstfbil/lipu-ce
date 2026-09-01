#!/usr/bin/env python3
import json
from pathlib import Path
from PIL import Image, ImageDraw, ImageFont

MANIFEST_PATH = Path("word_manifest.json")

FONT_PATH = "tools/Fairfax.ttf"
OUTPUT_PATH = "src/bitmap/gen_bitmap_glyphs"

GLYPH_WIDTH = 12
GLYPH_HEIGHT = 12
BYTES_PER_IMAGE = GLYPH_WIDTH*GLYPH_HEIGHT//8

assert GLYPH_HEIGHT*GLYPH_WIDTH == BYTES_PER_IMAGE*8, "Only bitmap sizes divisible by 8 are acceptable, try 12*12"

with open(MANIFEST_PATH) as f:
    words = json.load(f)
    
ucsur_chars = [chr(item["ucsur"]) for item in words]

def generate_glyphs():
    font = ImageFont.truetype(FONT_PATH, GLYPH_HEIGHT)

    # 1bpp bitmap format
    canvas = Image.new('1', (GLYPH_WIDTH, GLYPH_HEIGHT), color=(0))
    draw = ImageDraw.Draw(canvas)
    t = f"const unsigned char bitmap_glyphs[{len(ucsur_chars)}][{BYTES_PER_IMAGE}] = ""{\n"
    t2 = f"""#ifndef bitmap_include_file
#define bitmap_include_file
#ifdef __cplusplus
extern "C" """"{"f"""
#endif
extern const unsigned char bitmap_glyphs[{len(ucsur_chars)}][{BYTES_PER_IMAGE}];"""
    for i, code in enumerate(ucsur_chars):
        draw.text((0, 0), code, font=font, fill=(1))
        data = canvas.get_flattened_data()
        draw.rectangle([0,0,GLYPH_WIDTH,GLYPH_HEIGHT],0)
        bitmap = [0]*BYTES_PER_IMAGE
        for byte in range(BYTES_PER_IMAGE):
            for bit in range(8):
                bitmap[byte]<<=1
                bitmap[byte]|=data[byte*8 + bit]

        t += "  {" + ",".join(map(hex,bitmap)) + "},\n"
    with open(OUTPUT_PATH+".c","w") as f:
        f.write(t+"};")
    with open(OUTPUT_PATH+".h","w") as f:
        f.write(t2+f"""
#define bitmap_glyphs_len {len(ucsur_chars)}
#ifdef __cplusplus
""""}""""
#endif
#endif""")
    
    print(f"Succesfully generated bitmap glyphs from font {FONT_PATH}")
    
if __name__ == "__main__": generate_glyphs()