static int mobi_decompress_huffman_internal(MOBIBuffer *out, MOBIBuffer *in, MOBICDICT *huffcdic, size_t depth) {
    if (depth > 20) {
        ;
        return 3;
    }
    unsigned int symbol, index, cdic_index, maxcode, mincode, nextsymbol, nextrun, is_decompressed, symbol_length, offset;
    unsigned int code, buffer, bitsleft, bitcount, t1;
    unsigned long long bittable;
    int ret = 0;
    char bitoffset = 32;
    bitsleft = in->bytelen * 8;
    code_length = 0;
    buffer = mobi_buffer_fill64(in);
    while (!ret) {
        if (bitoffset <= 0) {
            bitoffset += 32;
            buffer = mobi_buffer_fill64(in);
        }
        code = (buffer >> bitoffset) & 0xffffffff;
        t1 = huffcdic[0x06 + (code >> 24)].value;
        code_length = t1 & 0x1f;
        maxcode = ((t1 >> 8) + 1) << (32 - code_length) - 1;
        if (!(t1 & 0x80)) {
            while (1) {
                if (code < huffcdic[0x106 + code_length].value) {
                    code_length++;
                } else {
                    maxcode = huffcdic[0x127 + code_length].value;
                    break;
                }
            }
        }
        bitoffset -= code_length;
        bitsleft -= code_length;
        if (bitsleft < 0) {
            break;
        }
        index = (maxcode - code) >> (32 - code_length);
        cdic_index = index >> huffcdic->cdic_shift;
        if (index >= huffcdic->cdic_count) {
            ;
            return 3;
        }
        offset = huffcdic->cdic_indexes[index];
        symbol = (huffcdic->cdic_data[cdic_index][offset] << 8) | huffcdic->cdic_data[cdic_index][offset + 1];
        is_decompressed = symbol >> 15;
        symbol &= 0x7fff;
        symbol_length = symbol & 0x7fff;
        if (is_decompressed) {
            mobi_buffer_addraw(out, &huffcdic->cdic_data[cdic_index][offset + 2], symbol_length);
            ret = out->error;
        } else {
            MOBIBuffer buf_sym;
            buf_sym.data = &huffcdic->cdic_data[cdic_index][offset + 2];
            buf_sym.offset = 0;
            buf_sym.maxlen = symbol_length;
            buf_sym.error = 0;
            ret = mobi_decompress_huffman_internal(out, &buf_sym, huffcdic, depth + 1);
        }
    }
    return ret;
}