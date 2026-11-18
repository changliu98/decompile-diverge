int func0(int n) {
    int n2 = n;
    int i = 0;
    int j = 2;
    while (1) {
        if (j * j > n2) {
            j++;
            continue;
        }
        int k = 0;
        while (1) {
            if (n2 % j == 0) {
                n2 /= j;
                k++;
            } else {
                break;
            }
        }
        int k2 = 0;
        int k3 = 1;
        while (1) {
            if (k2 + k3 <= k) {
                k2 += k3;
                i++;
                k3++;
            } else {
                break;
            }
        }
        if (n2 == 1) {
            break;
        }
        i++;
    }
    return i;
}