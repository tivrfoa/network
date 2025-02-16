#include <stdio.h>
#include "hpack.h"

int main() {
    uint8_t encoded[256];
    size_t encoded_size;
    char decoded_name[128];
    char decoded_value[128];

    // Encode a header
    hpack_encode_header(":method", "GET", encoded, &encoded_size);
    printf("Encoded Size: %zu\n", encoded_size);

    // Decode a header
    int ret = hpack_decode_header(encoded, encoded_size, decoded_name, decoded_value);
    if (ret == 0) {
        printf("Decoded: %s => %s\n", decoded_name, decoded_value);
    } else {
        printf("Decoding failed! ret = %d\n", ret);
    }

    return 0;
}

