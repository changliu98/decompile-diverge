char* func0(const char* arg) {
    static char result[100]; // Approximate size based on typical static buffer allocations
    int j = 0;
    
    for (int i = 0; arg[i] != '\0'; i++) {
        if (!isspace(arg[i])) {
            result[j++] = arg[i];
        }
    }
    result[j] = '\0';
    
    return result;
}