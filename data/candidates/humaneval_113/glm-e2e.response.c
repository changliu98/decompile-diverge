char **func0(char **strs, int n) {
    char **out = malloc(n * sizeof(char *));
    for (int i = 0; i < n; i++) {
        int count = 0;
        for (int j = 0; strs[i][j] != '\0'; j++) {
            if (strs[i][j] >= '0' && strs[i][j] <= '9') {
                if ((strs[i][j] - '0') % 2 == 1) {
                    count++;
                }
            }
        }
        out[i] = malloc(100);
        sprintf(out[i], "%d %d %d", count, count, count);
    }
    return out;
}