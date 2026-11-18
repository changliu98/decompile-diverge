size_t scan_ulong(char *str, unsigned_long *result)
{
    unsigned_long accumulator = 0; // Accumulator for the parsed unsigned long value
    size_t digit_count = 0;        // Counter for the number of digits processed
    // Loop while the current character is a valid digit ('0'-'9')
    // '0' is 0x30, so subtracting 0x30U gives the numeric value 0-9
    while ((int)str[digit_count] - 0x30U < 10) {
        // Convert character to numeric value and add to accumulator
        accumulator = accumulator * 10 + (ulong)((int)str[digit_count] - 0x30U);
        digit_count++; // Move to the next character
    }
    *result = accumulator; // Store the parsed value in the output pointer
    return digit_count; // Return the number of digits consumed
}