static unsigned int get_bits(struct heatshrink_decoder *hsd, unsigned char count)
{
    unsigned int decompressed = 0;
    if (count > 15)
        return -1;
    if (hsd->input_size == 0 && hsd->bit_index < (1 << (count - 1)))
        return -1;
    for (int i = 0; i < count; i++)
    {
        if (hsd->bit_index == 0)
        {
            if (hsd->input_size == 0)
                return -1;
            unsigned int input_index = hsd->input_index++;
            hsd->current_byte = hsd->buffers[input_index];
            if (hsd->input_index == hsd->input_size)
            {
                hsd->input_index = 0;
                hsd->input_size = 0;
            }
            hsd->bit_index = 0x80;
        }
        decompressed = (decompressed << 1);
        if (hsd->current_byte & hsd->bit_index)
            decompressed |= 1;
        hsd->bit_index = hsd->bit_index >> 1;
    }
    return decompressed;
}