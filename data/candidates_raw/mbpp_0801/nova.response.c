int func0(int a, int b, int c) {
    int i, j, k, l, m, n, o, p;
    int A[4], B[4];

    A[0] = a;
    A[1] = b;
    A[2] = c;
    B[0] = 0;
    B[1] = 0;
    B[2] = 0;
    B[3] = 0;

    for (i = 0; i < 4; i++) {
        for (j = 0; j < i; j++) {
            if (B[j] == A[i]) {
                B[j] = 1;
                break;
            }
        }
        if (j == i) {
            B[i]++;
        } else {
            i++;
        }
    }

    if (B[3] == 3) {
        o = 0;
    } else {
        o = 4 - B[3];
    }

    return o;
}