char* func0(const char* arg1, const char* arg2) {
    int i = 0;
    int j = 0;
    
    while (arg1[i] != '\0') {
        if (arg1[i] == ' ') {
            func0_str2[j] = arg2[0];
        } else {
            func0_str2[j] = arg1[i];
        }
        j++;
        i++;
    }
    
    func0_str2[j] = '\0';
    return func0_str2;
}