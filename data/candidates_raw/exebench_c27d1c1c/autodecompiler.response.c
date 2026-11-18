void reverse(char *str) {
    char *end = str;
    char tmp;

    if (str) {
        while (*end) {
            ++end;
        }
        --end;

        while (str < end) {
            tmp = *end;
            *end-- = *str;
            *str++ = tmp;
        }
    }
}