char* func0(int a, int b, int c, int d) {
    int sum = 0;
    if (a > 0) {
        sum += a;
    }
    if (b > 0) {
        sum += b;
    }
    if (c > 0) {
        sum += c;
    }
    if (d > 0) {
        sum += d;
    }

    char *str = (char *)malloc(sum + 1);
    if (str == NULL) {
        perror("malloc failed");
        exit(1);
    }

    int index = 0;
    
    for (int i = 0; i < a; i++) {
        str[index++] = 'p';
    }
    for (int i = 0; i < b; i++) {
        str[index++] = 'q';
    }
    for (int i = 0; i < c; i++) {
        str[index++] = 'r';
    }
    for (int i = 0; i < d; i++) {
        str[index++] = 's';
    }
    
    str[index] = '\0';
    
    return str;
}