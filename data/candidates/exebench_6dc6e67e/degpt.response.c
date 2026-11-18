void copia(char *destination, char *source_string)
{
    // Copy characters from source to destination until the null terminator is reached
    while (*source_string != '\0') {
        *destination = *source_string;  // Assign current character from source to destination
        source_string++;         // Move source pointer to the next character
        destination++;           // Move destination pointer to the next position
    }
    // Terminate the destination string with a null character
    *destination = '\0';
}