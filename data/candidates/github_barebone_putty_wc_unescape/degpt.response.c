// Unescapes backslash-escaped characters in the wildcard string and copies the result to output.
// Returns false if the wildcard contains unescaped special glob characters (*, ?, [, ]).
// Returns true on success.
_Bool wc_unescape(char *dest_buffer, char *src_pattern)
{
    // Iterate through each character of the wildcard string
    while (*src_pattern) {
        // Check if the current character is a backslash (escape character)
        if (*src_pattern == '\\') {
            // Move past the backslash
            src_pattern++;
            // If there is a character following the backslash
            if (*src_pattern) {
                // If output buffer is provided, copy the escaped character
                if (dest_buffer) {
                    *dest_buffer = *src_pattern;
                    dest_buffer++;
                }
                // Move past the escaped character
                src_pattern++;
            }
        // Check if the current character is an unescaped special glob character
        } else if (*src_pattern == '*' || *src_pattern == '?' || *src_pattern == '[' || *src_pattern == ']') {
            // Return false to indicate invalid wildcard pattern
            return false;
        // For all other characters, copy them as-is
        } else {
            // If output buffer is provided, copy the character
            if (dest_buffer) {
                *dest_buffer = *src_pattern;
                dest_buffer++;
            }
            // Move to the next character in wildcard
            src_pattern++;
        }
    }
    // Null-terminate the output string if buffer was provided
    if (dest_buffer) {
        *dest_buffer = '\0';
    }
    // Return true to indicate successful unescaping
    return true;
}