#include <stdio.h>
#include <stdlib.h>
#include <string.h>

extern uint32_t SwapDWord(uint8_t *p, int size);

typedef struct {
    uint8_t *data;
    uint32_t size;
} RTFStruct;

uint8_t* DecompressRTF(RTFStruct *input, uint32_t *out_size) {
    int32_t header_size = 0xcf;
    uint8_t *header = calloc(header_size + 1, 1);
    if (!header) {
        printf("%s%s%d", "Error", "Memory allocation failed", 0x4f);
        return NULL;
    }
    memcpy(header, "{\\rtf1\\ansi\\ansicpg1252\\deff0", header_size);

    uint8_t *src = input->data;
    uint32_t offset = 0;

    if (input->size < 0x14) {
        printf("Input too small");
        free(header);
        return NULL;
    }

    uint32_t comp_size = SwapDWord(src + offset, 4);
    offset += 4;
    uint32_t decomp_size = SwapDWord(src + offset, 4);
    offset += 4;
    uint32_t magic = SwapDWord(src + offset, 4);
    offset += 4;
    offset += 4; // Skip 4 bytes

    if (comp_size != input->size - 4) {
        printf("Size mismatch: %d != %d", comp_size, input->size - 4);
        free(header);
        return NULL;
    }

    uint8_t *dst = NULL;

    if (magic == 0x414c454d) { // "MELA"
        dst = calloc(decomp_size, 1);
        if (!dst) {
            printf("%s%s%d", "Error", "Memory allocation failed", 0x6c);
            free(header);
            return NULL;
        }
        memcpy(dst, src + 4, decomp_size);
        free(header);
        return dst;
    } else if (magic == 0x75465a4c) { // "LZFu"
        uint32_t bits = 0;
        uint32_t bits_buf = 0;
        
        if (header_size > 0x7fffffff - decomp_size) {
            printf("Integer overflow");
            exit(-1);
        }

        dst = calloc(header_size + decomp_size, 1);
        if (!dst) {
            printf("%s%s%d", "Error", "Memory allocation failed", 0x78);
            free(header);
            return NULL;
        }

        memcpy(dst, header, header_size);
        uint32_t dst_offset = header_size;

        while (dst_offset < header_size + decomp_size) {
            if ((bits % 8) == 0) {
                bits_buf = src[offset++];
            } else {
                bits_buf >>= 1;
            }
            bits++;

            if (bits_buf & 1) {
                uint32_t b1 = src[offset++];
                uint32_t b2 = src[offset++];
                uint32_t token = (b1 << 4) | (b2 >> 4);
                uint32_t count = (b2 & 0xf) + 2;
                token |= (dst_offset >> 12) << 12;
                if (token >= dst_offset) {
                    token -= 0x1000;
                }
                uint32_t end = token + count;
                
                while (token < end && dst_offset < header_size + decomp_size && token < header_size + decomp_size) {
                    dst[dst_offset++] = dst[token++];
                }
            } else {
                if (dst_offset >= header_size + decomp_size || offset >= input->size) {
                    printf("Overflow");
                    exit(-1);
                }
                dst[dst_offset++] = src[offset++];
            }
        }

        uint8_t *final_dst = calloc(decomp_size, 1);
        if (!final_dst) {
            printf("%s%s%d", "Error", "Memory allocation failed", 0x9e);
            free(header);
            free(dst);
            return NULL;
        }
        memcpy(final_dst, dst + header_size, decomp_size);
        free(dst);
        *out_size = decomp_size;
        free(header);
        return final_dst;
    } else {
        printf("Unknown compression: %x", magic);
    }

    free(header);
    return NULL;
}