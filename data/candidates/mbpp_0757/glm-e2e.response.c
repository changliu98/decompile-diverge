Adjusted size based on stack frame and typical usage

char* func0(char** arr, int n) {
    int count = 0;
    for (int i = 0; i < n; i++) {
        for (int j = i; j < n; j++) {
            int len = strlen(arr[i]);
            char rev[128]; // Size derived from stack allocation (0x80 bytes)
            for (int k = 0; k < len; k++) {
                rev[k] = arr[i][len - 1 - k];
            }
            rev[len] = '\0';
            
            if (strcmp(arr[j], rev) == 0) {
                count++;
            }
        }
    }
    sprintf(func0.result, "%d", count);
    return func0.result;
}