MOBI_RET mobi_decompress_huffman_internal(MOBIBuffer *buf_out, MOBIBuffer *buf_in, MOBIHuffCdic *huffcdic, size_t depth) {
    if (depth > 20) {
        return MOBI_DATA_CORRUPT;
    }
    MOBI_RET ret = MOBI_SUCCESS;
    int bitcount = 32;
    int bitsleft = buf_in->maxlen * 8;
    uint32_t code;
    uint64_t buffer = mobi_buffer_fill64(buf_in);
    while (ret == MOBI_SUCCESS) {
        if (bitcount <= 0) {
            bitcount += 32;
            buffer = mobi_buffer_fill64(buf_in);
        }
        code = (uint32_t)(buffer >> (bitcount - 32));
        uint32_t entry = huffcdic->table1[code >> 24];
        uint8_t code_length = (uint8_t)(entry & 0x1F);
        uint32_t maxcode = (((entry >> 8) + 1) << (32 - code_length)) - 1;
        if ((entry & 0x80) == 0) {
            while (code < huffcdic->mincode_table[code_length]) {
                code_length++;
            }
            maxcode = huffcdic->maxcode_table[code_length];
        }
        bitcount -= code_length;
        bitsleft -= code_length;
        if (bitsleft < 0) {
            break;
        }
        uint32_t index = (maxcode - code) >> (32 - code_length);
        uint16_t cdic_index = (uint16_t)(index >> huffcdic->code_length);
        if (index >= huffcdic->index_count) {
            return MOBI_DATA_CORRUPT;
        }
        uint32_t symbol_offset = huffcdic->symbol_offsets[index];
        uint16_t symbol_length = (uint16_t)(huffcdic->symbols[cdic_index][symbol_offset] & 0x7FFF);
        if ((huffcdic->symbols[cdic_index][symbol_offset] & 0x80) == 0) {
            MOBIBuffer buf_sym;
            buf_sym.data = huffcdic->symbols[cdic_index] + symbol_offset + 2;
            buf_sym.offset = 0;
            buf_sym.maxlen = symbol_length;
            buf_sym.error = MOBI_SUCCESS;
            ret = mobi_decompress_huffman_internal(buf_out, &buf_sym, huffcdic, depth + 1);
        } else {
            mobi_buffer_addraw(buf_out, huffcdic->symbols[cdic_index] + symbol_offset + 2, symbol_length);
            ret = buf_out->error;
        }
    }
    return ret;
}