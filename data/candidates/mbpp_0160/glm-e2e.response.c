Size is an assumption based on typical static buffers

char* func0(int a, int b, int c) {
    int i = 0;
    char *res;
    
    while (i * a <= c) {
        if ((c - i * a) % b == 0) {
            int j = i;
            int k = (c - i * a) / b;
            sprintf(func0_result, "%d %d", j, k);
            res = func0_result;
            return res;
        }
        i++;
    }
    
    res = "None";
    return res;
}