void func0(char *dest, char *src, int n) {
    int i = 0;
    bool inWord = false;

    while (true) {
        if (*src > 32) {
            inWord = true;
        }

        if (inWord && (i < n - 1)) {
            *dest++ = *src++;
            i++;
        } else if (!inWord && *src > 32) {
            inWord = true;
            i++;
        } else {
            src++;
        }

        if (i % 2 == 0) {
            *dest = '\0';
            break;
        }
    }
}