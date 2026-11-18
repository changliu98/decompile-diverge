int c_insensitive(char *a, char *b) {
    int i;
    for (i = 0;; i++) {
        if (a[i]!= '\0') {
            if (a[i] >= 'a' && a[i] <= 'z')
                a[i] -= 32;
        } else
            break;
    }
    for (i = 0;; i++) {
        if (b[i]!= '\0') {
            if (b[i] >= 'a' && b[i] <= 'z')
                b[i] -= 32;
        } else
            break;
    }
    int c;
    if (a[i] == '\0' && b[i] == '\0')
        c = 0;
    else if (a[i] > b[i])
        c = 1;
    else if (a[i] < b[i])
        c = -1;
    else
        for (;; i++) {
            if (a[i] == '\0' && b[i] == '\0')
                break;
        }
    return c;
}