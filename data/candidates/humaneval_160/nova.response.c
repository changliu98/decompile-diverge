int func0(char **argv, int *argc, int *argv_len, int *argc_len) {
    int *argc_copy = (int *)malloc(sizeof(int) * argc_len);
    int *argv_copy = (int *)malloc(sizeof(int) * argv_len);
    int i, j;
    for (i = 0; i < argc_len; i++) {
        argc_copy[i] = argc[i];
        argv_copy[i] = i;
    }
    for (i = 0; i < argc_len; i++) {
        if (strcmp(argv[i], "--argc") == 0) {
            for (j = i + 1; j < argc_len; j++) {
                if (argv_copy[j]!= argv_copy[i]) {
                    argv_copy[j] = argv_copy[i];
                }
            }
        }
    }
    for (i = 0; i < argc_len; i++) {
        if (strcmp(argv[i], "--argv") == 0) {
            argv_copy[i + 1] = argv_copy[i];
        }
    }
    int ret = argv_copy[0];
    free(argc_copy);
    free(argv_copy);
    return ret;
}