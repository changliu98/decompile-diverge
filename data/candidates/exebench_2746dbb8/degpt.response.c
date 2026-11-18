// Converts the input string to uppercase in-place.
// Iterates through each character until the null terminator is reached.
// If the character is a lowercase letter (ASCII 97-122), it converts it to uppercase by subtracting 0x20.
void convert_to_uppercase(char *string_buffer)
{
    for (; *string_buffer; string_buffer++) {
        // Check if the character is a lowercase letter
        if (*string_buffer > '`' && *string_buffer < '{') {
            // Convert to uppercase
            *string_buffer -= 0x20;
        }
    }
}