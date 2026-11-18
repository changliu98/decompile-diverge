int matchbrack(char *p, int c, int c2) {
    int negated = 0;
    int found = 0;
    int start;
    int end;

    if (*p == '!' || *p == '^') {
        negated = 1;
        p++;
    }

    if (*p == ']') {
        if (c == ']') {
            found = !negated;
            return found;
        }
        p++;
    } else if (*p == '-') {
        if (c == '-') {
            found = !negated;
            return found;
        }
        p++;
    }

    start = *(p - 1);
    while (*p != ']') {
        if (*p == '-' && *(p + 1) != ']') {
            p++;
            end = *p;
            if ((start <= c && c <= end) || (end <= c && c <= start)) {
                found = !negated;
                return found;
            }
        } else {
            start = *p;
            if (c == start || c2 == start) {
                found = !negated;
                return found;
            }
        }
        p++;
    }

    found = negated;
    return found;
}