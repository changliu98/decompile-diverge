void set_stimulus(uchar *output_buffer, char *input_string)
{
    // Iterate through the input string until the null terminator is reached
    for (; *input_string != '\0'; input_string++) {
        // Check if the current character is between '/' and '8' (exclusive)
        if ('/' < *input_string && *input_string < '8') {
            // Calculate the bit position based on the character's ASCII value
            // Subtract '0' (0x30) to get the numeric value, then mask with 0x1f to handle potential overflow
            // Clear the corresponding bit in the destination byte
            *output_buffer &= ~((byte)(1 << (*input_string - 0x30U & 0x1f)));
        }
    }
}