int func0(char *string, char *vowels) {
    int count = 0;
    char *s = string;
    char *v;
    while (*s != '\0') {
        v = vowels;
        while (*v != '\0') {
            if (*s == *v) {
                count++;
                break;
            }
            v++;
        }
        s++;
    }
    return count;
}