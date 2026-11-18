void ck_encrypt(char *str) {
    while (*str != '\0') {
        char c = *str;
        if (c == 'p' || c == '\\' || c == 'S') {
            // Skip encryption for these specific characters
        } else {
            *str = c ^ 0xF;
        }
        str++;
    }
}