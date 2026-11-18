void extract(char *str, int len, int n1, int n2, int n3, int *pos, int *out_len) {
    *pos = 0;
    *out_len = 0;

    if (n1 <= 0) {
        if (n1 < 0) {
            return;
        }
        if (n2 != 0 || n3 != 0) {
            n1 = 1;
        } else {
            *out_len = len;
            return;
        }
    }

    int i = 0;
    int count = 1;
    while (count < n1) {
        if (i < len && str[i] == (char)0xCB && str[i + 1] == (char)0xBE) {
            i++;
        } else {
            if (i >= len) {
                return;
            }
            i += 2;
            count++;
        }
    }

    int start = i;
    while (start < len && str[start] == (char)0xCB && str[start + 1] == (char)0xBE) {
        start++;
    }

    if (n2 <= 0) {
        if (n2 < 0) {
            return;
        }
        if (n3 == 0) {
            *pos = i;
            *out_len = start - i;
            return;
        }
        n2 = 1;
    }

    int j = 1;
    while (j < n2) {
        if (i < len && str[i] == (char)0xCB && str[i + 1] == (char)0xBD) {
            i++;
        } else {
            if (i >= len) {
                return;
            }
            i += 2;
            if (i > start) {
                return;
            }
            j++;
        }
    }

    int end = i;
    while (end < start && str[end] == (char)0xCB && str[end + 1] == (char)0xBD) {
        end++;
    }

    if (n3 <= 0) {
        if (n3 < 0) {
            return;
        }
        *pos = i;
        *out_len = end - i;
    }

    int k = 1;
    while (k < n3) {
        if (i < start && str[i] == (char)0xCB && str[i + 1] == (char)0xBC) {
            i++;
        } else {
            if (i >= len) {
                return;
            }
            i += 1;
            if (i > end) {
                return;
            }
            k++;
        }
    }

    int end2 = i;
    while (end2 < end && str[end2] == (char)0xCB && str[end2 + 1] == (char)0xBC) {
        end2++;
    }

    if (end2 >= end) {
        *pos = i;
        *out_len = end - i;
    } else {
        *pos = i;
        *out_len = end2 - i;
    }
}