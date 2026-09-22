NAME = LIPUCE
DESCRIPTION = "lipu CE - toki pona dictionary"
ICON = icon.png
VERSION_NO = v1.0

ARCHIVED = YES
COMPRESSED = YES
COMPRESSED_MODE = zx0

CFLAGS = -Wall -Wextra -Oz -DVERSION_NO='"$(VERSION_NO)"'
CXXFLAGS = -Wall -Wextra -Oz -DVERSION_NO='"$(VERSION_NO)"'

EXTRA_C_SOURCES = build/dictionary_data.c build/bitmap_glyphs.c

FLAVORS = core core-common core-uncommon core-obscure

CATEGORIES_core = core
CATEGORIES_core-common = core common
CATEGORIES_core-uncommon = core common uncommon
CATEGORIES_core-obscure  = core common uncommon obscure

all: $(FLAVORS)

$(FLAVORS):
	@echo "--- Building flavor $@ ---"
	python3 tools/build_assets.py --dictionary --glyphs --categories $(CATEGORIES_$@)
	$(MAKE) --no-print-directory build TARGET=LIPUCE-$@.8xp

define EXTRA_CLEAN
	rm -rf build
endef

include $(shell cedev-config --makefile)

.PHONY: all $(FLAVORS)