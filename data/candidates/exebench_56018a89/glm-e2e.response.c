void util_word_to_dec(char *str, unsigned int num) {
    char buf[10];
    int i = 0;
    int remainder;

    // Initialize buffer with '0's
    while (i < 10) {
        buf[i] = '0';
        i++;
    }

    // Null-terminate the buffer
    buf[10] = '\0';

    i = 9;
    // Extract digits from the number and place them in reverse order
    while (num > 0) {
        remainder = num % 10;
        num = num / 10;
        buf[i] = (char)remainder + '0';
        i--;
    }

    // Skip leading zeros
    i = 0;
    while (buf[i] == '0' && i < 9) {
        i++;
    }

    // Copy the remaining characters to the output string
    while (buf[i] != '\0') {
        *str = buf[i];
        str++;
        i++;
    }

    // Null-terminate the output string
    *str = '\0';
}