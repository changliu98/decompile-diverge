char* func0(const char* arg) {
    static char result[256]; // Assuming a reasonable buffer size based on the static address
    int i = 0;
    
    while (arg[i] != '\0') {
        result[i] = toupper(arg[i]);
        i++;
    }
    result[i] = '\0';
    
    return result;
}