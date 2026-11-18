char* func0(char** strings, int n) {
    char* best = "";
    int best_len = 0;
    
    for (int i = 0; i < n; i++) {
        char filtered[256];
        memset(filtered, 0, 256);
        int curr_len = 0;
        
        for (int j = 0; strings[i][j] != '\0'; j++) {
            if (strchr(filtered, strings[i][j]) == NULL) {
                int len = strlen(filtered);
                filtered[len] = strings[i][j];
                filtered[len + 1] = '\0';
                curr_len++;
            }
        }
        
        if (curr_len > best_len || 
           (curr_len == best_len && strcmp(strings[i], best) < 0)) {
            best = strings[i];
            best_len = curr_len;
        }
    }
    
    return best;
}