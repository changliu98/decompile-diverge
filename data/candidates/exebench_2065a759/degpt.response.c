int set_filename(char *destination, char *source)
{
    // Copy characters from from_name to to_name until a null terminator or '/' is encountered
    while (*source != '\0' && *source != '/') {
        *destination = *source;
        destination++;
        source++;
    }
    // Null-terminate the copied string in to_name
    *destination = '\0';
    // Return 1 if end of string was reached, 2 if '/' was encountered
    return (*source == '\0') ? 1 : 2;
}