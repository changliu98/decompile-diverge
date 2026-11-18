char* js_itoa(char* str, unsigned int value) {
    char buffer[8];
    int i = 0;

    // Convert value to string in reverse order
    while (value != 0) {
        buffer[i++] = (value % 10) + '0';
        value /= 10;
    }

    // Handle the case where value is 0
    if (i == 0) {
        buffer[i++] = '0';
    }

    // Copy the reversed buffer to the output string
    while (i > 0) {
        *str++ = buffer[--i];
    }

    // Null-terminate the string
    *str = '\0';

    // Return the original pointer
    return str;
}