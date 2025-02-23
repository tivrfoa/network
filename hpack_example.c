#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <nghttp2/nghttp2.h>

void print_header(const uint8_t *name, size_t name_len, const uint8_t *value, size_t value_len) {
    printf("  Name: %.*s, Value: %.*s\n", (int)name_len, name, (int)value_len, value);
}

int main() {
    nghttp2_hd_deflater *deflater;
    nghttp2_hd_inflater *inflater;
    int ret;

    // Initialize deflater and inflater
    ret = nghttp2_hd_deflate_new(&deflater, 4096);
    if (ret != 0) {
        fprintf(stderr, "Deflate init failed: %s\n", nghttp2_strerror(ret));
        return EXIT_FAILURE;
    }
    ret = nghttp2_hd_inflate_new(&inflater);
    if (ret != 0) {
        fprintf(stderr, "Inflate init failed: %s\n", nghttp2_strerror(ret));
        nghttp2_hd_deflate_del(deflater);
        return EXIT_FAILURE;
    }

    // Test Headers
    typedef struct {
        const char *name;
        const char *value;
    } header_pair;

    header_pair headers_to_encode[] = {
        { ":method", "GET" },
        { ":path", "/" },
        { "content-type", "application/json" },
        { NULL, NULL }
    };

    printf("\n--- Encoding Headers ---\n");

    for (int i = 0; headers_to_encode[i].name != NULL; ++i) {
        const char *name = headers_to_encode[i].name;
        const char *value = headers_to_encode[i].value;
        size_t name_len = strlen(name);
        size_t value_len = strlen(value);

        printf("\nEncoding header: Name: %s, Value: %s\n", name, value);

        nghttp2_nv nv = {
            (uint8_t *)name, (uint8_t *)value,
            name_len, value_len,
            NGHTTP2_NV_FLAG_NONE
        };
        uint8_t encoded_header[4096];
        size_t encoded_header_len = sizeof(encoded_header);

        // Encode
        ret = nghttp2_hd_deflate_hd(deflater, encoded_header, encoded_header_len, &nv, 1);
        if (ret < 0) {
            fprintf(stderr, "Encode failed: %s\n", nghttp2_strerror(ret));
        } else {
            encoded_header_len = ret;
            printf("Encoded header (length %zu):\n", encoded_header_len);
            for (size_t j = 0; j < encoded_header_len; ++j) {
                printf("%02x ", encoded_header[j]);
            }
            printf("\n");

            // Decode
            nghttp2_nv nv_out;
            int inflate_flags = 0;
            const uint8_t *in = encoded_header;
            size_t inlen = encoded_header_len;
            int in_final = 1; // This is the only block, so final

            ssize_t rv = nghttp2_hd_inflate_hd2(inflater, &nv_out, &inflate_flags, in, inlen, in_final);
            if (rv > 0) {
                printf("Decoded header:\n");
                print_header(nv_out.name, nv_out.namelen, nv_out.value, nv_out.valuelen);
            } else {
                fprintf(stderr, "Decode failed: %s\n", nghttp2_strerror(rv));
            }
        }
    }

    // Cleanup
    nghttp2_hd_deflate_del(deflater);
    nghttp2_hd_inflate_del(inflater);
    return EXIT_SUCCESS;
}
