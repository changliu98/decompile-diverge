char* itoa(int value, char* str, int base) {
    char digits[0x25];
    memcpy(digits, "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ", 0x25);
    
    char* ptr = str;
    char* low = str;

    // Check for invalid arguments
    if (ptr == NULL || base < 2 || base > 36) {
        return ptr;
    }

    // Only handle negative numbers for base 10
    if (base != 10 && value < 0) {
        return ptr;
    }

    // Handle zero explicitly
    if (value == 0) {
        *ptr++ = '0';
        *ptr = '\0';
        return ptr;
    }

    // Prepend minus sign for negative base-10 numbers
    if (base == 10 && value < 0) {
        *ptr++ = '-';
        value = -value;
    }

    // Convert the number to a string in reverse order
    while (value != 0) {
        int rem = value % base;
        *ptr++ = digits[rem];
        value /= base;
    }

    // Null-terminate the string
    *ptr = '\0';

    // Move ptr back to the last character written
    ptr--;

    // Reverse the string in place
    while (low < ptr) {
        char temp = *low;
        *low = *ptr;
        *ptr = temp;
        low++;
        ptr--;
    }

    return str;
}