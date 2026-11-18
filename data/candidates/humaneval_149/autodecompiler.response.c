char** func0(char** strings, int n, int* m) {
    *m = 0;
    for (int i = 0; i < n; i++) {
        if (strlen(strings[i]) % 2 == 0) {
            strings[*m] = strings[i];
            (*m)++;
        }
    }

    for (int i = 0; i < *m - 1; i++) {
        for (int j = 0; j < *m - i - 1; j++) {
            size_t len_j = strlen(strings[j]);
            size_t len_j1 = strlen(strings[j + 1]);

            if ((len_j > len_j1) || ((len_j == len_j1) && (strcmp(strings[j], strings[j + 1]) > 0))) {
                char* temp = strings[j];
                strings[j] = strings[j + 1];
                strings[j + 1] = temp;
            }
        }
    }

    char** result = (char**)malloc(*m * sizeof(char*));
    for (int i = 0; i < *m; i++) {
        result[i] = strings[i];
    }

    return result;
}