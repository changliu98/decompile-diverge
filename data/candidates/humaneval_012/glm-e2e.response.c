char* func0(char** strings, int num_strings) {
    char* longest = ""; // Corresponds to the address loaded at 0x11ef
    int max_len = 0;
    
    for (int i = 0; i < num_strings; i++) {
        int current_len = strlen(strings[i]);
        if (current_len > max_len) {
            longest = strings[i];
            max_len = current_len;
        }
    }
    
    return longest;
}