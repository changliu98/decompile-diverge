1

uint16_t __cdecl get_bits(heatshrink_decoder *hsd, uint8_t count)
{
    uint16_t accumulator = 0;

    // The maximum allowed bit count is 15 (0xF)
    if (count > 0xF)
        return INVALID_BITS;

    // Pre-check to ensure we have enough bits left in the input buffer.
    // If there's no input left and we don't even have enough bits in the 
    // current byte to satisfy the request, return an error.
    if (hsd->input_size == 0 && hsd->bit_index < (1 << (count - 1)))
        return INVALID_BITS;

    for (uint8_t i = 0; i < count; ++i)
    {
        // If we've exhausted the bits in the current byte, fetch the next one
        if (hsd->bit_index == 0)
        {
            // If the buffer is empty, we can't fetch anything
            if (hsd->input_size == 0)
                return INVALID_BITS;

            // Read the next byte from the input buffer
            uint16_t idx = hsd->input_index;
            hsd->input_index = idx + 1;
            hsd->current_byte = hsd->buffers[idx];

            // Wrap around and clear input_size if we've reached the end of the buffer
            if (hsd->input_index == hsd->input_size)
            {
                hsd->input_index = 0;
                hsd->input_size = 0;
            }
            
            // Reset bit mask to the most significant bit (0x80)
            hsd->bit_index = 0x80;
        }

        // Shift the accumulator left by 1 to make room for the next bit
        accumulator <<= 1;

        // If the current bit is set, set the least significant bit of the accumulator
        if ((hsd->current_byte & hsd->bit_index) != 0)
            accumulator |= 1;

        // Shift the bit mask right by 1 to process the next bit.
        // (The cast to int preserves potential sign-bit behavior from the original decompilation)
        hsd->bit_index = (int)hsd->bit_index >> 1;
    }

    return accumulator;
}