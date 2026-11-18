int __cdecl dv_write_ssyb_id(uint8_t syb_num, uint8_t fr, uint8_t *buf)
{
    // Determine the first byte based on the symbol number
    if (syb_num != 0 && syb_num != 6)
    {
        if (syb_num == 11)
            *buf = (fr << 7) | 0x7F; // Set lower 7 bits to 1
        else
            *buf = (fr << 7) | 0x0F; // Set lower 4 bits to 1
    }
    else
    {
        *buf = (fr << 7) | 0x0F;    // Set lower 4 bits to 1
    }

    // Second byte: Store syb_num in the lower nibble, set upper nibble to 1
    buf[1] = (syb_num & 0x0F) | 0xF0;

    // Third byte: Set all bits to 1 (0xFF)
    buf[2] = 0xFF;

    // Total bytes written
    return 3;
}