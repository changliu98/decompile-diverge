int func0(const char *a, const char *b) {
    int diff_count = 0;
    int len = strlen(a);
    
    for (int i = 0; i < len; i++) {
        if (a[i] != b[i]) {
            diff_count++;
        }
    }
    
    if (diff_count % 2 == 0) {
        return diff_count / 2;
    } else {
        return -1;
    }
}