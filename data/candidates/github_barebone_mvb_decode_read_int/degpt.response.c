// Reads a variable-length integer (LEB128 encoding) from the input buffer.
// The function decodes up to 5 bytes, supporting values up to 32 bits.
// Each byte uses the most significant bit (MSB) as a continuation flag:
// - If MSB is 0, it's the last byte of the integer.
// - If MSB is 1, more bytes follow.
//
// Parameters:
//   in  - Pointer to the input buffer containing the encoded integer.
//   out - Pointer to the output variable where the decoded integer will be stored.
//
// Returns:
//   The number of bytes consumed from the input buffer (1 to 5).
int read_int(uint8_t *input_buffer, uint32_t *decoded_value)
{
    // Initialize output with the first 7 bits of the first byte.
    *decoded_value = *input_buffer & 0x7f;
    // If the continuation bit (MSB) is not set, the integer is complete.
    if (*input_buffer < 0x80) return 1;
    
    // Add the next 7 bits, shifted left by 7 positions.
    *decoded_value |= (input_buffer[1] & 0x7f) << 7;
    // If the continuation bit is not set, the integer is complete.
    if (input_buffer[1] < 0x80) return 2;
    
    // Add the next 7 bits, shifted left by 14 positions.
    *decoded_value |= (input_buffer[2] & 0x7f) << 14;
    // If the continuation bit is not set, the integer is complete.
    if (input_buffer[2] < 0x80) return 3;
    
    // Add the next 7 bits, shifted left by 21 positions.
    *decoded_value |= (input_buffer[3] & 0x7f) << 21;
    // If the continuation bit is not set, the integer is complete.
    if (input_buffer[3] < 0x80) return 4;
    
    // Add the final 4 bits (since we only need 32 bits total), shifted left by 28.
    // Cast to uint32_t to ensure proper shifting behavior.
    *decoded_value |= (uint32_t)input_buffer[4] << 28;
    // Return the total number of bytes consumed (5 bytes for a full 32-bit value).
    return 5;
}