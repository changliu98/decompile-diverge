char** func0(int* arr, int n, char* suffix) {
    char** out = malloc(n * 2 * sizeof(char*));
    int j = 0;
    for (int i = 0; i < n; i++) {
        asprintf(&out[j], "%d%s", arr[i], suffix);
        j++;
        out[j] = suffix;
        j++;
    }
    return out;
}