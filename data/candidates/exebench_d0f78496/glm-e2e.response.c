char* read_int(char *str, int max_len, int *result) {
    int val = 0;
    
    while (max_len-- > 0 && *str >= '0' && *str <= '9') {
        val = val * 10 + (*str - '0');
        str++;
    }
    
    *result = val;
    return str;
}