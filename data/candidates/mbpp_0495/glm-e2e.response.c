Approximate size based on typical BSS allocation

char* func0(char* param) {
    int j = 0;
    int i = 0;
    
    while (param[i] != '\0') {
        if (param[i] >= 'a' && param[i] <= 'z') {
            // It's a lowercase letter, skip copying it
        } else {
            result[j] = param[i];
            j++;
        }
        i++;
    }
    
    result[j] = '\0';
    return result;
}