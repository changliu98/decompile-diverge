void combain_sorted_array(int *a, int *b, int *c) {
    int *p, *q, *r;
    p = a;
    q = b;
    r = c;
    while (1) {
        if (p < a + 5) {
            if (q < b + 5) {
                if (*p < *q) {
                    *r = *p;
                    p++;
                    r++;
                } else {
                    *r = *q;
                    q++;
                    r++;
                }
            } else {
                *r = *p;
                p++;
                r++;
            }
        } else {
            if (q < b + 5) {
                *r = *q;
                q++;
                r++;
            } else {
                break;
            }
        }
    }
}