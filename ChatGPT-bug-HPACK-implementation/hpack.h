#ifndef HPACK_H
#define HPACK_H

#include <stdint.h>
#include <stddef.h>

#define HPACK_DYNAMIC_TABLE_SIZE 4096

// Static table entry
typedef struct {
    const char *name;
    const char *value;
} hpack_static_entry_t;

// Dynamic table entry
typedef struct {
    char *name;
    char *value;
} hpack_dynamic_entry_t;

// Dynamic table structure
typedef struct {
    hpack_dynamic_entry_t *entries;
    size_t size;
    size_t capacity;
} hpack_dynamic_table_t;

// HPACK Functions
void hpack_init_dynamic_table(hpack_dynamic_table_t *table);
void hpack_free_dynamic_table(hpack_dynamic_table_t *table);
void hpack_add_dynamic_entry(hpack_dynamic_table_t *table, const char *name, const char *value);
int hpack_encode_header(const char *name, const char *value, uint8_t *output, size_t *output_size);
int hpack_decode_header(const uint8_t *input, size_t input_size, char *name, char *value);

#endif // HPACK_H

