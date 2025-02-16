#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "hpack.h"

// HPACK Static Table (subset of RFC 7541 predefined headers)
static const hpack_static_entry_t hpack_static_table[] = {
    {":authority", ""},
    {":method", "GET"},
    {":method", "POST"},
    {":path", "/"},
    {":path", "/index.html"},
    {":scheme", "http"},
    {":scheme", "https"},
    {":status", "200"},
    {":status", "404"},
    {":status", "500"},
};

// Number of static entries
static const size_t HPACK_STATIC_TABLE_SIZE = sizeof(hpack_static_table) / sizeof(hpack_static_table[0]);

// Initialize Dynamic Table
void hpack_init_dynamic_table(hpack_dynamic_table_t *table) {
    table->entries = NULL;
    table->size = 0;
    table->capacity = 0;
}

// Free Dynamic Table
void hpack_free_dynamic_table(hpack_dynamic_table_t *table) {
    for (size_t i = 0; i < table->size; i++) {
        free(table->entries[i].name);
        free(table->entries[i].value);
    }
    free(table->entries);
}

// Add Header to Dynamic Table
void hpack_add_dynamic_entry(hpack_dynamic_table_t *table, const char *name, const char *value) {
    if (table->size >= HPACK_DYNAMIC_TABLE_SIZE) {
        return; // Prevent overflow
    }

    table->entries = realloc(table->entries, (table->size + 1) * sizeof(hpack_dynamic_entry_t));
    table->entries[table->size].name = strdup(name);
    table->entries[table->size].value = strdup(value);
    table->size++;
}

// Encode a Header Field
int hpack_encode_header(const char *name, const char *value, uint8_t *output, size_t *output_size) {
    size_t index = 0;

    // Check Static Table
    for (size_t i = 0; i < HPACK_STATIC_TABLE_SIZE; i++) {
        if (strcmp(hpack_static_table[i].name, name) == 0) {
            output[index++] = (uint8_t)(i + 1); // Index into static table
            strcpy((char *)&output[index], value);
            index += strlen(value);
            *output_size = index;
            return 0;
        }
    }

    // If not in static table, encode name-value pair manually
    output[index++] = 0x40; // Literal header field
    strcpy((char *)&output[index], name);
    index += strlen(name);
    output[index++] = (uint8_t)strlen(value);
    strcpy((char *)&output[index], value);
    index += strlen(value);

    *output_size = index;
    return 0;
}

// Decode a Header Field
int hpack_decode_header(const uint8_t *input, size_t input_size, char *name, char *value) {
    size_t index = 0;

    // Check if it's an indexed field (Static Table)
    if (input[0] & 0x80) {
        size_t static_index = input[0] & 0x7F;
        if (static_index > 0 && static_index <= HPACK_STATIC_TABLE_SIZE) {
            strcpy(name, hpack_static_table[static_index - 1].name);
            strcpy(value, hpack_static_table[static_index - 1].value);
            return 0;
        }
    }

    // Literal Header Field (Dynamic Table or New Entry)
    if (input[0] & 0x40) {
        index++;
        strcpy(name, (char *)&input[index]);
        index += strlen(name) + 1;
        strcpy(value, (char *)&input[index]);
        return 0;
    }

    return -1; // Error decoding
}

