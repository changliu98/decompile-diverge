bool func0(const char *s1, const char *s2) {
    int len1 = strlen(s1);
    int len2 = strlen(s2);

    // Check if every character in s1 exists in s2
    for (int i = 0; i < len1; i++) {
        bool found = false;
        for (int j = 0; j < len2; j++) {
            if (s1[i] == s2[j]) {
                found = true;
                break;
            }
        }
        if (!found) {
            return false;
        }
    }

    // Check if every character in s2 exists in s1
    for (int i = 0; i < len2; i++) {
        bool found = false;
        for (int j = 0; j < len1; j++) {
            if (s2[i] == s1[j]) {
                found = true;
                break;
            }
        }
        if (!found) {
            return false;
        }
    }

    return true;
}