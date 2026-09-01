NAME = LIPUCE
DESCRIPTION = "lipu CE - toki pona dictionary"
ICON = icon.png
VERSION_NO = v1.0

ARCHIVED = YES
COMPRESSED = YES
COMPRESSED_MODE = zx0

CFLAGS = -Wall -Wextra -Oz -Ibuild -DVERSION_NO='"$(VERSION_NO)"'
CXXFLAGS = -Wall -Wextra -Oz -Ibuild -DVERSION_NO='"$(VERSION_NO)"'

DEPS = build/dictionary_data.c build/bitmap_glyphs.c
EXTRA_C_SOURCES = build/dictionary_data.c build/bitmap_glyphs.c

# add 'uncommon' and/or 'obscure' to include more words
WORD_CATEGORIES = core common

define EXTRA_CLEAN
	rm -rf build
endef

include $(shell cedev-config --makefile)

build/word_manifest.json:
	WORD_CATEGORIES="$(WORD_CATEGORIES)" python3 tools/generate_manifest.py

build/dictionary_data.c: build/word_manifest.json
	python3 tools/generate_dictionary.py

build/bitmap_glyphs.c: build/word_manifest.json
	python3 tools/generate_glyphs.py