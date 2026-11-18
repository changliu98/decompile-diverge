__attribute__((used)) static int smacker_decode_tree(BitstreamContext *bs, HuffEntry *he, int code, int bits)
{
    int ret;

    if (!bitstream_read_bit(bs)) {
        if (he->next_free >= 257) {
            av_log(NULL, 16, "Tree size exceeded!\n");
            return -0x41444249;
        }
        if (bits) {
            he->code[he->next_free] = code;
            he->bits[he->next_free] = bits;
        } else {
            he->code[he->next_free] = 0;
            he->bits[he->next_free] = 0;
        }
        he->symbol[he->next_free] = bitstream_read(bs, 8);
        he->next_free++;
        if (he->max_bits < bits)
            he->max_bits = bits;
        return 0;
    } else {
        bits++;
        ret = smacker_decode_tree(bs, he, code | (1 << (bits - 1)), bits);
        if (ret)
            return ret;
        return smacker_decode_tree(bs, he, code, bits - 1);
    }
}