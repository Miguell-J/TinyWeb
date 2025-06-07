#ifndef HACKING_H
#define HACKING_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Display an error message and exit
static inline void fatal(const char *message) {
    char error_message[100];
    // Use snprintf para evitar overflow
    snprintf(error_message, sizeof(error_message), "[!!] Fatal Error %s", message);
    perror(error_message);
    exit(EXIT_FAILURE);
}

// Error-checked malloc wrapper
static inline void *ec_malloc(size_t size) {
    void *ptr = malloc(size);
    if (ptr == NULL) {
        fatal("in ec_malloc() on memory allocation");
    }
    return ptr;
}

// Dump memory buffer in hex and ASCII
static inline void dump(const unsigned char *data_buffer, unsigned int length) {
    unsigned int i, j;
    for (i = 0; i < length; i++) {
        printf("%02x ", data_buffer[i]);
        if ((i % 16 == 15) || (i == length - 1)) {
            for (j = 0; j < 15 - (i % 16); j++)
                printf("   ");
            printf("| ");
            for (j = i - (i % 16); j <= i; j++) {
                unsigned char byte = data_buffer[j];
                if (byte > 31 && byte < 127)
                    printf("%c", byte);
                else
                    printf(".");
            }
            printf("\n");
        }
    }
}

#endif // HACKING_H
