void func0(const char *src, char *dst) {
    int i = 0;
    while (src[i] != '\0') {
        // Shift character by 4, wrap around within 'a'..'z' using modulo 26
        int shifted = ((src[i] - 'a' + 4) % 26) + 'a';
        dst[i] = (char)shifted;
        i++;
    }
    dst[i] = '\0';
}