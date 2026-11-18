int stbi__parse_zlib(struct stbi__context *z, int parse_header) {
    int final;
    int type;

    if (parse_header) {
        if (stbi__zeof(z) == 0) {
            return 0;
        }
    }

    do {
        // z->num_bits = 0;
        *((int*)((char*)z + 0x10)) = 0;
        // z->code_buffer = 0;
        *((int*)((char*)z + 0x18)) = 0;
        // z->hit_zeof = 0; (or similar field)
        *((int*)((char*)z + 0x14)) = 0;

        final = stbi__zreceive(z, 1);
        type = stbi__zreceive(z, 2);

        if (type == 0) {
            if (stbi__parse_uncompressed_block(z) == 0) {
                return 0;
            }
        } else if (type == 3) {
            return 0;
        } else if (type == 1) {
            if (stbi__zbuild_huffman((struct stbi__context*)((char*)z + 0x3c), stbi__default_length, 288) == 0) {
                return 0;
            }
            if (stbi__zbuild_huffman((struct stbi__context*)((char*)z + 0x820), stbi__default_distance, 32) == 0) {
                return 0;
            }
        } else { // type == 2
            if (stbi__compute_huffman_codes(z) == 0) {
                return 0;
            }
        }

        if (stbi__parse_huffman_block(z) == 0) {
            return 0;
        }
    } while (!final);

    return 1;
}