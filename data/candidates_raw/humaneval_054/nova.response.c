bool func0(char *s1, char *s2) {
    int len1 = strlen(s1);
    int len2 = strlen(s2);
    int i, j;
    bool is_same;
    for (i = 0; i < len1; i++) {
        bool is_found = false;
        for (j = 0; j < len2; j++) {
            if (s1[i] == s2[j]) {
                is_found = true;
                break;
            }
        }
        if (!is_found) {
            is_same = false;
            break;
        }
    }
    if (!is_same) {
        return false;
    }
    for (i = 0; i < len2; i++) {
        bool is_found = false;
        for (j = 0; j < len1; j++) {
            if (s2[i] == s1[j]) {
                is_found = true;
                break;
            }
        }
        if (!is_found) {
            is_same = false;
            break;
        }
    }
    if (!is_same) {
        return false;
    }
    return true;
}