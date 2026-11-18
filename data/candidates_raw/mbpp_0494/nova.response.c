char *func0(int *digits, int n) {
    int i, j = 0;
    for (i = 0; i < n; i++)
        j += digits[i] * pow(10, n - 1 - i);
    char *s = (char *)malloc(sizeof(char) * 12);
    sprintf(s, "%d", j);
    return s;
}