int func0(char *s) {
    int i, sum = 0;
    for (i = 0; s[i] != '\0'; i++) {
        if (s[i] >= 'A' && s[i] <= 'Z') {
            sum += s[i];
        }
    }
    return sum;
}