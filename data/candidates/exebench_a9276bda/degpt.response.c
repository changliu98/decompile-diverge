// Converts an unsigned integer to a string representation in the provided buffer.
// The buffer must be at least 10 bytes long to hold up to 10 digits plus the null terminator.
// Returns a pointer to the first character of the resulting string.
char * intToString(char *buffer, uint number)
{
    // Initialize the 10th position (index 9) as the null terminator.
    // This ensures the string is properly terminated even if the number has fewer than 10 digits.
    buffer[9] = '\0';

    // Iterate backwards from the last digit position (index 8) to the first (index 0).
    // This allows us to build the string from least significant digit to most significant.
    for (int index = 8; index >= 0; index--) {
        // Convert the last digit of val to its ASCII character representation.
        buffer[index] = (number % 10) + '0';
        
        // Remove the last digit from val by integer division.
        number /= 10;
        
        // If val is now zero, we have processed all digits, so stop early.
        if (number == 0) break;
    }

    // Return a pointer to the first non-zero digit (or the null terminator if val was 0).
    // Note: 'i' is the index after the last processed digit, so buff + i points to the start of the string.
    return buffer + index;
}