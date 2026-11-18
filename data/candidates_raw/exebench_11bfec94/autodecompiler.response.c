char *to_hex(long int n, char *hex) {
    char hex_chars[16] = "0123456789ABCDEF";
    int i;
    for (i = sizeof(n)*2; i >= 0; i--) {
        hex[i] = hex_chars[n % 16];
        n >>= 4;
    }
    hex[sizeof(n)*2 + 1] = '\0';
    return hex;
}