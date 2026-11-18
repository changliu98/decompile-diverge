void __cdecl sjis2jis(uint8_t *p1, uint8_t *p2)
{
    uint8_t high_byte = *p1;
    uint8_t low_byte = *p2;
    
    uint8_t high_offset;
    uint8_t low_offset;

    // 1. Determine the offset for the high byte
    // SJIS high bytes in the 0x81-0x9F range subtract 0x70 (112)
    // SJIS high bytes in the 0xE0-0xFC range subtract 0x80 (-128)
    if (high_byte < 0xA0)
        high_offset = 0x70; // 112
    else
        high_offset = 0x80; // -128 in signed char, but 0x80 in unsigned

    // 2. Determine the offset for the low byte
    if (low_byte >= 0x9F) {
        low_offset = 0x7E; // 126
    } else {
        // Evaluates to 31 (0x1F) if low_byte <= 0x7F
        // Evaluates to 32 (0x20) if low_byte is 0x80-0x9E
        low_offset = (low_byte > 0x7F) + 0x1F; 
    }

    // 3. Calculate the new high byte
    // The boolean condition acts as 1 if low_byte < 0x9F, acting as a carry/borrow bit.
    // This is equivalent to: (high_byte - high_offset) * 2 - (low_byte < 0x9F ? 1 : 0)
    *p1 = (high_byte - high_offset) * 2 - (low_byte < 0x9F);

    // 4. Calculate the new low byte
    *p2 = low_byte - low_offset;
}