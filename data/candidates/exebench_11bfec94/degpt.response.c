void to_hex(long value, char *hex_string)
{
    // Lookup table for hexadecimal characters (0-9, A-F)
    const char hex_digits[] = "0123456789ABCDEF";
    int index;
    // Iterate 4 times to process 4 nibbles (16 bits total)
    for (index = 3; index >= 0; index--) {
        // Extract the least significant nibble and map to hex character
        hex_string[index] = hex_digits[value % 0x10];
        // Shift right by 4 bits to process the next nibble
        value >>= 4;
    }
    // Null-terminate the resulting hex string
    hex_string[4] = '\0';
}