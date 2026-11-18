// Copies the string pointed to by s into the buffer pointed to by buf.
// Stops when the null terminator of s is encountered and appends a null terminator to buf.
void gdb_strcpy(char *destination_buffer, char *source_string) {
    // Copy characters from s to buf until the null terminator is reached
    while (*source_string) {
        *destination_buffer++ = *source_string++;
    }
    // Append null terminator to the destination buffer
    *destination_buffer = '\0';
}