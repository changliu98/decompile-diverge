int smacker_decode_tree(BitstreamContext *bc, HuffContext *hc,
                               uint32_t prefix, int length)
{
    int bit;
    int r;

    bit = bitstream_read_bit(bc);
    if (bit) {
        length++;
        r = smacker_decode_tree(bc, hc, prefix, length);
        if (r)
            return r;
        prefix |= 1 << (length - 1);
        return smacker_decode_tree(bc, hc, prefix, length);
    } else {
        if (hc->current >= 256) {
            av_log(NULL, 16, "Tree size exceeded!\n");
            return -0x41444E49;
        }
        if (length) {
            hc->bits[hc->current] = prefix;
            hc->lengths[hc->current] = length;
        } else {
            hc->bits[hc->current] = 0;
            hc->lengths[hc->current] = 0;
        }
        hc->values[hc->current] = bitstream_read(bc, 8);
        hc->current++;
        if (length > hc->maxlength)
            hc->maxlength = length;
        return 0;
    }
}