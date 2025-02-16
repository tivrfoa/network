// Code from Gemini 2.0 Flash
//
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

// Function 1: Original (Potentially Problematic) Approach
void copy_string_original(uint8_t *output, const char *value, int index) {
    strcpy((char *)&output[index], value); // Potential issues: strict aliasing, alignment
}

// Function 2: Using memcpy (If you know the size)
void copy_string_memcpy(uint8_t *output, const char *value, int index, size_t n) {
    memcpy(&output[index], value, n);
}

// Function 3: Copying byte by byte
void copy_string_byte_by_byte(uint8_t *output, const char *value, int index) {
    for (size_t i = 0; value[i] != '\0'; i++) {
        output[index + i] = (uint8_t)value[i];
    }
}

// Function 4: Using char* (Recommended for Strings)
void copy_string_char_ptr(char *output, const char *value, int index) {
    strcpy(&output[index], value);
}

void print_uint8_as_string(uint8_t *buffer) {
    for(int i = 0; buffer[i] != 0; i++){
        printf("%c", buffer[i]);
    }
    printf("\n");
}


int main() {
    // Test data
    const char *test_string = "Hello, world!";
    // int index = 5; // Gemini bug ...
    int index = 0;
    size_t n = 8; // Number of bytes to copy for memcpy example

    // Test with uint8_t* and original approach (copy_string_original)
    uint8_t buffer1[50] = {0}; // Initialize to 0
    copy_string_original(buffer1, test_string, index);
    printf("Original: %s\n", buffer1);
    print_uint8_as_string(buffer1);

    // Test with uint8_t* and memcpy
    uint8_t buffer2[50] = {0};
    copy_string_memcpy(buffer2, test_string, index, n);
    printf("memcpy: %s\n", buffer2);

    // Test with uint8_t* and byte by byte
    uint8_t buffer3[50] = {0};
    copy_string_byte_by_byte(buffer3, test_string, index);
    printf("Byte by byte: %s\n", buffer3);

    // Test with char* (recommended for strings)
    char buffer4[50] = {0};
    copy_string_char_ptr(buffer4, test_string, index);
    printf("char*: %s\n", buffer4);



    //Demonstrating potential issue with Original approach and alignment
    // uint8_t buffer5[50] = {0};
    // uint32_t *aligned_int_ptr = (uint32_t*)&buffer5[2]; //Potentially misaligned int
    // *aligned_int_ptr = 0x12345678; //Writing an int value
    // copy_string_original(buffer5, test_string, index); //This could cause issues
    // printf("Original with potential alignment issue: %s\n", buffer5);


    return 0;
}
