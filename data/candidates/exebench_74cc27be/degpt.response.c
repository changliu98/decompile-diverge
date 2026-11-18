// Copies the string from src to dest
void copy_string(char *destination, char *source)
{
    // Iterate through each character of src until the null terminator
    while (*source) {
        // Copy the current character from src to dest and increment both pointers
        *destination++ = *source++;
    }
    // Terminate the destination string with a null character
    *destination = '\0';
}