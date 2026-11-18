char*** func0(int a, int b, int c) {
    char*** arr = malloc(c * sizeof(char**));
    for (int i = 0; i < c; i++) {
        arr[i] = malloc(b * sizeof(char*));
        for (int j = 0; j < b; j++) {
            arr[i][j] = malloc(a * sizeof(char));
            for (int k = 0; k < a; k++) {
                arr[i][j][k] = '*';
            }
        }
    }
    return arr;
}