int mobi_decompress_huffman_internal(mobi_buffer *out_buf, mobi_buffer *in_buf, mobi_huffman *huff, uint32_t depth) {
    int ret;
    uint32_t error = 0;
    int8_t bit_pos = 32;
    int32_t bits_left = in_buf->field_10 * 8;
    uint8_t code_len = 0;
    uint64_t val64;
    uint32_t val32;
    uint32_t entry;
    uint32_t mask;
    uint32_t code;
    uint32_t offset;
    uint16_t idx1;
    uint16_t idx2;
    uint32_t sym;
    uint32_t is_raw;
    uint8_t *ptr;
    
    // A structure to pass data recursively, corresponding to the stack frame at -0x80
    struct {
        uint8_t *ptr;
        uint32_t len;
        uint32_t field_8;
        uint32_t field_10;
    } recursive_data;

    if (depth > 20) {
        return 3;
    }

    val64 = mobi_buffer_fill64(in_buf);

    while (error == 0) {
        if (bit_pos <= 0) {
            bit_pos += 32;
            val64 = mobi_buffer_fill64(in_buf);
        }

        val32 = (uint32_t)((val64 >> bit_pos) & 0xFFFFFFFF);
        
        entry = huff->table1[val32 >> 24];
        code_len = entry & 0x1F;
        mask = ((entry >> 8) + 1) << (32 - code_len) - 1;

        if ((entry & 0x80) == 0) {
            while (val32 < huff->table2[code_len]) {
                code_len++;
            }
            mask = huff->table3[code_len];
        }

        bit_pos -= code_len;
        bits_left -= code_len;
        if (bits_left < 0) {
            break;
        }

        code = (mask - val32) >> (32 - code_len);
        offset = code >> huff->shift;

        if (offset >= huff->max_offset) {
            return 3;
        }

        idx1 = huff->ptr1[offset];
        idx2 = huff->ptr2[idx2_idx][idx1]; // Simplified representation of pointer arithmetic
        sym = (huff->ptr2[idx2_idx][idx1] << 8) | huff->ptr2[idx2_idx][idx1 + 1];
        
        is_raw = sym >> 15;
        sym &= 0x7FFF;

        if (is_raw) {
            mobi_buffer_addraw(out_buf, huff->ptr2[idx2_idx] + idx1 + 2, sym);
            error = out_buf->field_18;
        } else {
            recursive_data.ptr = huff->ptr2[idx2_idx] + idx1 + 2;
            recursive_data.len = sym;
            recursive_data.field_8 = 0;
            recursive_data.field_10 = 0;
            
            error = mobi_decompress_huffman_internal(out_buf, (mobi_buffer*)&recursive_data, huff, depth + 1);
        }
    }

    ret = error;
    return ret;
}