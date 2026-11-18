void func0(char *out, char **strs, int n, char *unused) {
    int max_score = -1000;
    char *best_str = NULL;
    
    for (int i = 0; i < n; i++) {
        char *s = strs[i];
        int score = 0;
        
        for (int j = 0; s[j] != '\0'; j++) {
            char c = s[j];
            if (c >= 'A' && c <= 'Z') {
                score++;
            } else if (c >= 'a' && c <= 'z') {
                score--;
            }
        }
        
        if (score > max_score) {
            max_score = score;
            best_str = s;
        }
    }
    
    sprintf(out, "%s %s", unused, best_str);
}