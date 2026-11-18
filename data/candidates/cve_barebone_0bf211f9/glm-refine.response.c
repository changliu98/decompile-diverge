int __cdecl smacker_decode_tree(BitstreamContext *bc, HuffContext *hc, uint32_t prefix, int length)
{
    // If the bit is 1, we branch into an internal node and recurse left and right.
    if (bitstream_read_bit(bc)) 
    {
        int r = smacker_decode_tree(bc, hc, prefix, length + 1);
        if (r)
            return r;

        // Right child: append a '1' bit to the prefix at the current depth
        uint32_t right_prefix = (1u << length) | prefix;
        return smacker_decode_tree(bc, hc, right_prefix, length + 1);
    }

    // If the bit is 0, we hit a leaf node. Check if we've exceeded the 256-byte leaf limit.
    if (hc->current >= 256) 
    {
        av_log(NULL, AV_LOG_ERROR, "Tree size exceeded!\n");
        return AVERROR_INVALIDDATA; // -1094995529 (0xBEBBBEBB)
    }

    // Store the leaf's prefix and length. If length is 0 (root is a leaf), store 0s.
    if (length) 
    {
        hc->bits[hc->current] = prefix;
        hc->lengths[hc->current] = length;
    } 
    else 
    {
        hc->bits[hc->current] = 0;
        hc->lengths[hc->current] = 0;
    }

    // Read the 8-bit value associated with this leaf and advance the current index
    hc->values[hc->current++] = bitstream_read(bc, 8);
    
    // Update the maximum code length observed so far
    if (hc->maxlength < length)
        hc->maxlength = length;

    return 0;
}