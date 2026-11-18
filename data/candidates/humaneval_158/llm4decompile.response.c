char *func0(char **words, int count)
{
    int i, j, k, len, maxu, u;
    char *max, unique[256];

    max = "";
    maxu = 0;
    for (i = 0; i < count; i++) {
        memset(unique, 0, 256);
        u = 0;
        for (j = 0; words[i][j]; j++) {
            if (strchr(unique, words[i][j]) == NULL) {
                k = strlen(unique);
                unique[k] = words[i][j];
                unique[k + 1] = 0;
                u++;
            }
        }
        if (u > maxu || (u == maxu && strcmp(words[i], max) < 0)) {
            max = words[i];
            maxu = u;
        }
    }

    return max;
}