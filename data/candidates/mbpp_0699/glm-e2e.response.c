int func0(const char *s1, const char *s2) {
    int diff_count = 0;
    int len = strlen(s1);
    
    for (int i = 0; i < len; i++) {
        if (s1[i] != s2[i]) {
            diff_count++;
        }
    }
    
    if (diff_count % 2 == 0) {
        return diff_count / 2;
    } else {
        return -1;
    }
}