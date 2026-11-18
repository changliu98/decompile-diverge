void strcpymax(char *destination, char *source, int max_length)
{
    int index;
    // Copy characters from src to dest until null terminator is reached or n-1 characters are copied
    for (index = 0; source[index] != '\0' && index < max_length - 1; index++) {
        destination[index] = source[index];
    }
    // Ensure the destination string is null-terminated
    destination[index] = '\0';
}