char ** func0(int * test_tup, int size, char * K) {
    int i;
    int j = 0;
    char ** res = malloc(size * 2 * sizeof(char *));
    for (i = 0; i < size; i++) {
        asprintf(&res[j++], "%d", test_tup[i]);
        res[j++] = K;
    }
    return res;
}