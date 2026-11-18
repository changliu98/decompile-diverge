int last_slash(char *path, int *number_found, int *path_size)
{
    int last_slash_index = 0; // Stores the index of the last found slash
    int slash_count = 0; // Counter for the number of slashes found
    int char_index;
    // Iterate through the path string up to 256 characters or null terminator
    for (char_index = 0; path[char_index] != '\0' && char_index < 0x100; char_index++) {
        if (path[char_index] == '/') {
            slash_count++; // Increment slash count
            last_slash_index = char_index; // Update last slash index
        }
    }
    *number_found = slash_count; // Output the total number of slashes found
    *path_size = char_index; // Output the length of the path processed
    return last_slash_index; // Return the index of the last slash
}