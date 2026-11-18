int mobi_decompress_huffman_internal(mobi_buffer *out_buf, mobi_buffer *in_buf, huff_info *info, uint64_t depth) {
    int ret = 0;
    int error = 0;
    char bit_pos = 32;
    int32_t bits_left;
    uint32_t code = 0;
    char code_len = 0;
    uint32_t max_code = 0;
    uint32_t symbol = 0;
    uint16_t val1 = 0;
    uint32_t val2 = 0;
    uint32_t is_raw = 0;
    uint16_t idx1 = 0;
    uint8_t *ptr = NULL;

    if (depth > 20) {
        return 3;
    }

    bits_left = in_buf->field_8 * 8;
    uint64_t bit_buf = mobi_buffer_fill64(in_buf);

    while (error == 0) {
        if (bit_pos <= 0) {
            bit_pos += 32;
            bit_buf = mobi_buffer_fill64(in_buf);
        }

        code = (uint32_t)((bit_buf >> bit_pos) & 0xFFFFFFFF);
        
        max_code = info->table1[code >> 24];
        code_len = max_code & 0x1F;
        max_code = ((max_code >> 8) + 1) << (32 - code_len) - 1;

        if ((max_code & 0x80) == 0) {
            while (code < info->table2[code_len]) {
                code_len++;
            }
            max_code = info->table3[code_len];
        }

        bit_pos -= code_len;
        bits_left -= code_len;
        if (bits_left < 0) {
            break;
        }

        symbol = (max_code - code) >> (32 - code_len);
        idx1 = symbol >> info->field_10;

        if (symbol >= info->field_0) {
            return 3;
        }

        val1 = info->ptr_528[symbol];
        ptr = info->ptr_528[idx1 * 8];
        
        val2 = (ptr[val1] << 8) | ptr[val1 + 1];
        is_raw = val2 >> 15;
        val2 &= 0x7FFF;

        if (is_raw) {
            mobi_buffer_addraw(out_buf, ptr + val1 + 2, val2);
            error = out_buf->field_18;
        } else {
            struct {
                void *data;
                uint64_t len;
                int32_t error;
            } local_buf;
            
            ptr = ptr + val1 + 2;
            local_buf.data = ptr;
            local_buf.len = val2;
            local_buf.error = 0;
            
            error = mobi_decompress_huffman_internal(out_buf, (mobi_buffer*)&local_buf, info, depth + 1);
        }
    }

    return error;
}