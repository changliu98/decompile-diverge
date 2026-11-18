char *func0(int n) {
    int total_length = 2;
    for (int i = 1; i <= n; i++) {
        total_length += snprintf(NULL, 0, "%d", i);
    }

    char *buffer = (char *)malloc(total_length);
    if (buffer == NULL) {
        return NULL;
    }

    char *ptr = buffer;
    ptr += sprintf(ptr, "->");
    
    for (int i = 1; i <= n; i++) {
        ptr += sprintf(ptr, "%d", i);
    }

    return buffer;
}