res at 0x40a0

char* func0(char** arr, int n) {
    char sep[2] = ", "; // Initialized from a 2-byte string literal at 0x2004
    int i = 0;
    
    strcpy(res, ""); // Copies an empty string literal from 0x201e
    
    for (i = 0; i < n; i++) {
        strcat(res, arr[i]);
        if (i < n - 1) {
            strcat(res, sep);
        }
    }
    
    return res;
}