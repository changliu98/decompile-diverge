char *func0(char *s, int n) {
    int len = strlen(s);
    char *result = (char *)malloc(sizeof(char) * (len + 1));
    int i = 0;
    while (i < len) {
        result[i] = s[(i + n) % len];
        i++;
    }
    result[len] = '\0';
    return result;
}