Located at 0x2004

void dummyfunc(char *str) {
    int i = 0;
    char *ptr = &global_var;
    
    while (str[i] != '\0') {
        str[i] = ptr[i];
        i++;
    }
}