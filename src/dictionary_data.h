#ifndef __DICTIONARY_DATA_H__
#define __DICTIONARY_DATA_H__

#define TOKI_PONA_ALPHABET_SIZE 14

#include <stdint.h>

typedef enum
{
    CORE,
    COMMON,
    UNCOMMON,
    OBSCURE
} word_category_t;

typedef struct
{
    const char *word;
    uint16_t sp_glyph_id;
    uint16_t def_offset;
    word_category_t category;

} word_entry_t;

typedef struct
{
    int word_count;
    const word_entry_t *words;
    const char *def_string_table;
    const int letter_index[TOKI_PONA_ALPHABET_SIZE];
} dictionary_db_t;

extern const dictionary_db_t g_dictionary;

#endif // __DICTIONARY_DATA_H__