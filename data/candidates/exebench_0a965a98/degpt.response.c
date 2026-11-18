// Copies up to 'num' characters from string 't' to string 's'
// Ensures the destination string 's' is null-terminated
// Returns 0 on success
int new_strcpy(char *destination, char *source, int max_length)
{
    int index;
    // Copy characters from t to s until null terminator of t is reached or num characters are copied
    for (index = 0; source[index] != '\0' && index < max_length; index++) {
        destination[index] = source[index];
    }
    // Null-terminate the destination string
    destination[index] = '\0';
    return 0;
}