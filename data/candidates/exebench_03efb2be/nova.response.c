void swap(int a[10]) {
    int *p, *q, t;
    p = a;
    q = a;
    for (int i = 0; i < 6; i++) {
        for (int j = i; j < 6; j++) {
            if (*(p + j) < *(p + i)) {
                p = p + j;
            }
            if (*(q + j) > *(q + i)) {
                q = q + j;
            }
        }
        t = *(p);
        *(p) = *(q);
        *(q) = t;
        p = a + 1;
        q = a + 1;
        for (int j = 0; j < 6; j++) {
            if (*(p + j) < *(p + i)) {
                p = p + j;
            }
            if (*(q + j) > *(q + i)) {
                q = q + j;
            }
        }
        t = *(p);
        *(p) = *(q);
        *(q) = t;
        p = a + 2;
        q = a + 2;
        for (int j = 0; j < 6; j++) {
            if (*(p + j) < *(p + i)) {
                p = p + j;
            }
            if (*(q + j) > *(q + i)) {
                q = q + j;
            }
        }
        t = *(p);
        *(p) = *(q);
        *(q) = t;
        p = a + 3;
        q = a + 3;
        for (int j = 0; j < 6; j++) {
            if (*(p + j) < *(p + i)) {
                p = p + j;
            }
            if (*(q + j) > *(q + i)) {
                q = q + j;
            }
        }
        t = *(p);
        *(p) = *(q);
        *(q)