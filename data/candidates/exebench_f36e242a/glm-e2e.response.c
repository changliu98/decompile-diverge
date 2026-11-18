int ltos(char *dest, long val) {
    char buffer[32];
    char *buf_ptr = buffer;
    long abs_val;

    // Compute the absolute value of val
    if (val < 0) {
        abs_val = -val;
    } else {
        abs_val = val;
    }

    // Extract digits in reverse order
    while (abs_val > 9) {
        *buf_ptr++ = (char)((abs_val % 10) + '0');
        abs_val /= 10;
    }

    // Prepend minus sign if the original number was negative
    if (val < 0) {
        *dest++ = '-';
    }

    // Write the last remaining digit
    *dest++ = (char)(abs_val + '0');

    // Copy the reversed digits from the local buffer to the destination
    // to correct the order
    while (buf_ptr > buffer) {
        *dest++ = *--buf_ptr;
    }

    // Null-terminate the string
    *dest = '\0';

    return 0;
}