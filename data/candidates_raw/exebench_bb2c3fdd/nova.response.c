void func0(char *str) {
    int i, j, k, l;
    char temp;
    for (i = 0;; i++) {
        if (str[i] == '\0')
            break;
    }
    for (j = 0, k = i - 1; j <= k; j++, k--) {
        if (j > k)
            break;
        temp = str[j];
        str[j] = str[k];
        str[k] = temp;
    }
}