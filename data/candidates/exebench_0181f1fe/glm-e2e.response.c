int ellipsis(char *str, int size) {
    int ret = 0;
    int high_bit = 0;
    int remaining = 0;
    char *ptr = str;

    if (size < 0 || str == NULL) {
        return 0;
    }

    if (size < 3) {
        str[size] = '\0';
        return 1;
    }

    remaining = size - 3;
    
    // Skip characters until we have room for 3 trailing dots or hit the null terminator
    while (*ptr != '\0' && remaining != 0) {
        if (high_bit == 0) {
            if ((*ptr & 0x80) != 0) {
                high_bit = 1;
            }
        } else {
            high_bit = 0;
        }
        ptr++;
        remaining--;
    }

    // Skip any remaining characters up to the null terminator
    remaining = 3;
    while (*ptr != '\0' && --remaining != 0) {
        ptr++;
    }

    // If we reached the end of the string exactly as we used up our limit
    if (*ptr == '\0' && remaining == 0) {
        str[size] = '\0';
        ptr--;
        *ptr = '.';
        ptr--;
        *ptr = '.';
        
        // Check for broken multi-byte character boundary and replace with dot if needed
        if (high_bit == 0 && (*(ptr - 1) & 0x80) != 0) {
            ptr--;
            *ptr = '.';
        }
    }

    return 1;
}