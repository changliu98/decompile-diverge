char* func0(const char* arg) {
    int i = 0;
    int j = 0;
    
    while (arg[i] != '\0') {
        if (isalpha(arg[i])) {
            if (i != 0) {
                if (!isspace(arg[i - 1]) && !isalpha(arg[i - 1])) {
                    buffer[j++] = '_';
                }
            }
            buffer[j++] = tolower(arg[i]);
        } else {
            buffer[j++] = arg[i];
        }
        i++;
    }
    buffer[j] = '\0';
    
    return buffer;
}