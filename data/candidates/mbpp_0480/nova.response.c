char func0(char *string) {
    int i, j, k, l, m, n;
    int count[256];
    char result;

    n = strlen(string);

    memset(count, 0, sizeof(count));

    for (i = 0, j = 0; i < n; i++)
        count[string[i]]++;

    for (i = 0, result = 'a'; i < n; i++) {
        if (count[string[i]] < count[result]) {
            result = string[i];
        }
    }

    return result;
}