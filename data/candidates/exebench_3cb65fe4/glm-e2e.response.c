char* get_begin(const char *str, int *sign) {
    int i = 0;
    int s = 1;
    
    while (str[i] == '+' || str[i] == '-') {
        if (str[i] == '-') {
            s = -s;
        }
        i++;
    }
    
    *sign = s;
    return (char*)(str + i);
}