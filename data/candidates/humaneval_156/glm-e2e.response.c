void func0(int n, char *out) {
    // Corresponds to the first memcpy at 0x1212
    // Size 0x68 (104 bytes) = 13 elements * 8 bytes (pointers)
    const char *strings[] = {
        "M", "CM", "D", "CD", "C", "XC", "L", "XL", "X", "IX", "V", "IV", "I"
    };
    
    // Corresponds to the second memcpy at 0x122a
    // Size 0x34 (52 bytes) = 13 elements * 4 bytes (ints)
    const int values[] = {
        1000, 900, 500, 400, 100, 90, 50, 40, 10, 9, 5, 4, 1
    };
    
    int i = 0;
    out[0] = '\0';
    
    while (n > 0) {
        if (n >= values[i]) {
            strcat(out, strings[i]);
            n -= values[i];
        } else {
            i++;
        }
    }
}