size_t itoa(int value, char *str, int base) {
    size_t ret = 0;
    char buffer[16];
    int idx = 0;

    // Check if base is valid (between 2 and 36)
    if (base < 2 || base > 36) {
        return 0;
    }

    // Handle the special case where value is 0
    if (value == 0) {
        str[0] = '0';
        return 1;
    }

    // Extract digits in reverse order
    // Note: This loop only works correctly for positive numbers.
    // For negative numbers, the `div` instruction will yield negative remainders.
    while (value != 0) {
        int rem = value % base;
        value /= base;
        buffer[idx++] = digits[rem];
    }

    // Reverse the extracted digits and place them into the output string
    for (size_t i = 0; i < (size_t)idx; i++) {
        str[i] = buffer[idx - 1 - i];
    }

    return idx;
}