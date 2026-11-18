int func0(char *s1, char *s2) {
    char s1_[128], s2_[128];
    int i, j;
    for (i = 0;; i++) {
        if (s1[i]!= '/') {
            s1_[i] = s1[i];
        } else {
            s1_[i] = '\0';
            break;
        }
    }
    int n1 = atoi(s1_);
    for (j = 0;; j++, i++) {
        if (s1[i]!= '\0') {
            s2_[j] = s1[i];
        } else {
            s2_[j] = '\0';
            break;
        }
    }
    int n2 = atoi(s2_);
    i = 0;
    for (j = 0;; j++, i++) {
        if (s2[i]!= '\0') {
            s2_[j] = s2[i];
        } else {
            s2_[j] = '\0';
            break;
        }
    }
    int n3 = atoi(s2_);
    int ans;
    if (n2 * n1 % n3 == 0) {
        ans = 1;
    } else {
        ans = 0;
    }
    return ans;
}