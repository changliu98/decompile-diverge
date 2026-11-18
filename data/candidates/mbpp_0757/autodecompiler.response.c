char* func0(char** arr, int n) {
    char str[100];
    char rev[100];
    int count = 0;
    int i = 0;
    while (1) {
        if (i >= n) break;
        int j = i;
        while (1) {
            if (j >= n) break;
            int len = strlen(arr[i]);
            int k = 0;
            while (1) {
                if (k >= len) break;
                rev[k] = arr[i][len - 1 - k];
                k++;
            }
            rev[len] = '\0';
            if (strcmp(arr[j], rev) == 0) count++;
            j++;
        }
        i++;
    }
    sprintf(str, "%d", count);
    strcpy(func0_result, str);
    return func0_result;
}