// Converts a single byte value to its two-character hexadecimal string representation.
// hex: Pointer to a buffer of at least 2 characters to store the result.
// val: The byte value to convert.
void gsm_hex_from_byte(char *hex_buffer, int byte_value)
{
    // Extract the upper nibble (4 bits) and map it to the corresponding hex character.
    *hex_buffer = "0123456789abcdef"[(int)(byte_value >> 4 & 0xf)];
    // Extract the lower nibble (4 bits) and map it to the corresponding hex character.
    hex_buffer[1] = "0123456789abcdef"[(int)(byte_value & 0xf)];
}