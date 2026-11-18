int ckstrncpy(char *destination_buffer, char *source_buffer, int buffer_size)
{
    int character_index;
    // Validate input parameters: length must be at least 1, and pointers must not be NULL
    if (buffer_size < 1 || source_buffer == NULL || destination_buffer == NULL) {
        // If destination is valid, ensure it is null-terminated
        if (destination_buffer != NULL) {
            *destination_buffer = '\0';
        }
        // Return 0 to indicate failure or no characters copied
        return 0;
    }
    // Copy characters from src to dest up to len-1 characters or until null terminator is reached
    for (character_index = 0; source_buffer[character_index] != '\0' && character_index < buffer_size - 1; character_index++) {
        destination_buffer[character_index] = source_buffer[character_index];
    }
    // Null-terminate the destination string
    destination_buffer[character_index] = '\0';
    // Return the number of characters copied (excluding the null terminator)
    return character_index;
}