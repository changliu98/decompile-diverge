int64_t vcolon(uint8_t *input_buffer, int64_t buffer_length, int64_t current_index)
{
    // If the current index is at the end of the JSON string, return an error code
    if (current_index == buffer_length) {
        return -(current_index + 1);
    }
    // If the current character is a colon, return the index of the next character
    if (input_buffer[current_index] == ':') {
        return current_index + 1;
    }
    // Iterate through the remaining characters in the JSON string
    while (current_index + 1 < buffer_length) {
        current_index++;
        uint8_t current_char = input_buffer[current_index];
        // Check if the character is not a space, carriage return, or a control character (ASCII <= 9)
        if (current_char != 0x20 && current_char != 0xd && current_char > 9) {
            // If the character is a colon, return the index of the next character
            if (current_char == ':') {
                return current_index + 1;
            }
            // If the character is not a colon, return an error code
            return -(current_index + 1);
        }
    }
    // If no colon is found, return an error code
    return -(current_index + 2);
}