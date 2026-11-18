static int func0(const char *s, int i, int *pmin, int *pmax, int *pstep,
                 int *perror) {
    int c;
    int min, max, step;

    if (s[i] == '^') {
        i++;
        *perror = 1;
    } else
        *perror = 0;

    c = s[i];
    switch (c) {
    case L'+':
        i++;
        *pmin = 1;
        *pmax = INFINITY;
        step = 8;
        break;
    case L'-':
        i++;
        *pmin = -INFINITY;
        *pmax = 1;
        step = 8;
        break;
    case L'*':
        *pmin = 1;
        *pmax = INFINITY;
        step = 8;
        break;
    case L'?':
        *pmin = 0;
        *pmax = 1;
        step = 8;
        break;
    default:
        *pmin = i;
        *pmax = i;
        step = 8;
        break;
    }

    for (;;) {
        c = s[i];
        if (c == '\0')
            break;
        if (c!= L']')
            break;
        i++;
        *perror = 1;
        step = 3;
    }

    *pmin = i;
    *pmax = i;
    step = 8;
    return step;
}