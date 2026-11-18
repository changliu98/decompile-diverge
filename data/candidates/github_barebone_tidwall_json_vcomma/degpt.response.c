int64_t vcomma(uint8_t *buffer, int64_t buffer_length, int64_t current_index, uint8_t expected_delimiter)
{
    // Check if the current index has reached the end of the JSON buffer
    if (current_index == buffer_length) {
        // Return negative index to indicate error (not found)
        return -(current_index + 1);
    }
    // Check if the current character is a comma
    if (buffer[current_index] == ',') {
        // Return the current index as the position of the comma
        return current_index;
    }
    // Skip whitespace characters (space, carriage return, tab)
    while (current_index < buffer_length) {
        uint8_t current_char = buffer[current_index];
        // If the character is not whitespace and not a control character (ASCII <= 9)
        if (current_char != 0x20 && current_char != 0x0d && current_char > 9) {
            // If the character matches the expected end delimiter, return its index
            if (current_char == expected_delimiter) {
                return current_index;
            }
            // Otherwise, it's an unexpected character; return negative index to indicate error
            return -(current_index + 1);
        }
        // Move to the next character
        current_index++;
    }
    // If the loop completes without finding the delimiter, return negative index to indicate error
    return -(current_index + 1);
}