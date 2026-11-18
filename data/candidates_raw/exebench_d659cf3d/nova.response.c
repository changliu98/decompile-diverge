int func0(char *str, char c) {
    char *p = str;
    char *q = NULL;
    int count = 0;
    int i = 0;

    while (1) {
        if (*p!= c) {
            if (*p == '\0') {
                i = 0;
                break;
            }
            p++;
        } else {
            q = p;
            while (1) {
                if (*p!= c) {
                    if (*p == '\0') {
                        i = count;
                        break;
                    }
                    p++;
                    count++;
                } else {
                    *q = *(p + 1);
                    q++;
                    p++;
                }
            }
            break;
        }
    }
    return i;
}