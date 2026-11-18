char *func0(char **dictionary, int dictSize) {
    int i, j, k, l, m, n;
    char word[100];
    char *longest;
    int longest_len = 0;

    for (i = 0; i < dictSize; i++) {
        for (j = i + 1; j < dictSize; j++) {
            l = strlen(dictionary[i]);
            for (k = 0, m = 0; m < l; m++) {
                word[k++] = dictionary[i][l - 1 - m];
            }
            word[l] = '\0';
            if (strcmp(dictionary[j], word) == 0) {
                longest_len++;
                break;
            }
        }
    }

    sprintf(longest, "%d", longest_len);
    return longest;
}