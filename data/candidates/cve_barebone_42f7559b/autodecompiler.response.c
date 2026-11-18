int mobi_decompress_huffman_internal(MOBIBuffer *out, MOBIBuffer *in, MOBICDHuff *huffcdic, size_t depth) {
    if (depth > 20) {
        ;
        return 3;
    }
    int ret = 0;
    char bitsleft = sizeof(unsigned long long)*8, bitcount = sizeof(unsigned long long)*8;
    unsigned long long buffer = in->data ? mobi_buffer_fill64(in) : 0;
    unsigned int codeword, maxcode, symbol, index, cdic_index, code_length = 0;

    while (ret == 0) {
        if (bitcount <= 0) {
            bitcount += sizeof(unsigned long long)*8;
            buffer = mobi_buffer_fill64(in);
        }
        codeword = (unsigned int)((buffer >> bitcount) & ((1ULL << (sizeof(unsigned long long)*8)) - 1));
        t1 = huffcdic->firstcodeword[codeword >> (32 - 8)];
        code_length = (t1 & 0x1f);
        maxcode = ((t1 >> 8) + 1) << (sizeof(unsigned long long)*8 - code_length);
        if (!(t1 & 0x80)) {
            while (codeword < huffcdic->firstcodeword[32 + code_length]) {
                code_length++;
            }
            maxcode = huffcdic->lastcodeword[code_length];
        }
        bitcount -= code_length;
        bitsleft -= code_length;
        if (bitsleft < 0) {
            break;
        }
        index = (maxcode - codeword) >> (sizeof(unsigned long long)*8 - code_length);
        cdic_index = (unsigned short)(index >> huffcdic->cdicshift);
        if (index >= huffcdic->cdiclen) {
            ;
            return 3;
        }
        symbol = (unsigned int)((huffcdic->cdictab[cdic_index][index] << 8) | huffcdic->cdictab[cdic_index][index + 1]);
        unsigned int is_decompressed = symbol >> 15;
        symbol &= 0x7fff;
        if (is_decompressed) {
            mobi_buffer_addraw(out, &huffcdic->cdictab[cdic_index][index + 2], symbol);
            ret = out->error;
        } else {
            MOBIBuffer buf_sym = { .data = &huffcdic->cdictab[cdic_index][index + 2], .offset = 0, .maxlen = symbol, .error = 0 };
            ret = mobi_decompress_huffman_internal(out, &buf_sym, huffcdic, depth + 1);
        }
    }
    return ret;
}