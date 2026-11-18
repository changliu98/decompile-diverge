int func0(char **strings, int n, char *target, char ***res) {
    int len = strlen(target);
    int i, j;
    *res = (char **)malloc(n * sizeof(char *));
    for (i = 0, j = 0; i < n; i++) {
        if (strncmp(strings[i], target, len) == 0)
            (*res)[j++] = strings[i];
    }
    return j;
}