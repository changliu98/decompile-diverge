int filenvercmp(const char *s1, ptrdiff_t l1, const char *s2, ptrdiff_t l2) {
    int is_empty1;
    int is_empty2;
    int is_dot1;
    int is_dot2;
    int is_dotdot1;
    int is_dotdot2;
    int same_len;
    int cmp;
    int res;

    // Check if strings are empty
    if (l1 < 0) {
        is_empty1 = (s1[0] == '\0');
    } else {
        is_empty1 = (l1 == 0);
    }

    if (l2 < 0) {
        is_empty2 = (s2[0] == '\0');
    } else {
        is_empty2 = (l2 == 0);
    }

    // Handle empty string comparisons
    if (is_empty1) {
        return is_empty2 ? 0 : -1;
    }
    if (is_empty2) {
        return 1;
    }

    // Check for "." (current directory)
    if (s1[0] == '.') {
        if (s2[0] != '.') {
            return -1;
        }

        if (l1 < 0) {
            is_dot1 = (s1[1] == '\0');
        } else {
            is_dot1 = (l1 == 1);
        }

        if (l2 < 0) {
            is_dot2 = (s2[1] == '\0');
        } else {
            is_dot2 = (l2 == 1);
        }

        if (is_dot1) {
            return is_dot2 ? 0 : -1;
        }
        if (is_dot2) {
            return 1;
        }

        // Check for ".." (parent directory)
        if (s1[1] == '.') {
            if (l1 < 0) {
                is_dotdot1 = (s1[2] == '\0');
            } else {
                is_dotdot1 = (l1 == 2);
            }
        } else {
            is_dotdot1 = 0;
        }

        if (s2[1] == '.') {
            if (l2 < 0) {
                is_dotdot2 = (s2[2] == '\0');
            } else {
                is_dotdot2 = (l2 == 2);
            }
        } else {
            is_dotdot2 = 0;
        }

        if (is_dotdot1) {
            return is_dotdot2 ? 0 : -1;
        }
        if (is_dotdot2) {
            return 1;
        }
    } else {
        if (s2[0] == '.') {
            return 1;
        }
    }

    // Compare prefixes and full strings
    ptrdiff_t p1 = file_prefixlen(s1, &l1);
    ptrdiff_t p2 = file_prefixlen(s2, &l2);

    same_len = (p1 == l1 && p2 == l2);

    cmp = verrevcmp(s1, p1, s2, p2);
    if (cmp != 0 || !same_len) {
        res = cmp;
    } else {
        res = verrevcmp(s1, l1, s2, l2);
    }

    return res;
}