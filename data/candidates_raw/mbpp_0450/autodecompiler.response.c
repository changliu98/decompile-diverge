char** func0(char** input, int n, int m, int* output_size) {
    int size = 0;
    static char* func0_result[1000000];
    for(int i = 0; i < n; i++) {
        if(strlen(input[i]) == m)
            func0_result[size++] = input[i];
    }
    *output_size = size;
    return func0_result;
}