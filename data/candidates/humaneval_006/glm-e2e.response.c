int* func0(const char *str, int *count) {
    int *arr = NULL;
    int depth = 0;
    int max_depth = 0;
    int i = 0;
    int n = 0;

    for (i = 0; str[i] != '\0'; i++) {
        char c = str[i];
        if (c == '(') {
            depth++;
            if (depth > max_depth) {
                max_depth = depth;
            }
        } else if (c == ')') {
            depth--;
            if (depth == 0) {
                arr = (int *)realloc(arr, (n + 1) * sizeof(int));
                arr[n] = max_depth;
                n++;
                max_depth = 0;
            }
        }
    }

    *count = n;
    return arr;
}