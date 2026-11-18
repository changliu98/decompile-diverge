int func0(char **arr, int n, const char *str, char ***out_arr) {
    int str_len = strlen(str);
    char **filtered = malloc(n * sizeof(char *));
    *out_arr = filtered;
    
    int count = 0;
    for (int i = 0; i < n; i++) {
        if (strncmp(arr[i], str, str_len) == 0) {
            filtered[count] = arr[i];
            count++;
        }
    }
    
    return count;
}