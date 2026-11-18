int func0(int n, int *a) {
    int i = 0;
    int m = n;
    while (1) {
        if (m % 53 == 0) {
            m = m / 53;
            a[i] = 53;
            i++;
        } else if (m % 47 == 0) {
            m = m / 47;
            a[i] = 47;
            i++;
        } else if (m % 31 == 0) {
            m = m / 31;
            a[i] = 31;
            i++;
        } else if (m % 23 == 0) {
            m = m / 23;
            a[i] = 23;
            i++;
        } else if (m % 19 == 0) {
            m = m / 19;
            a[i] = 19;
            i++;
        } else if (m % 17 == 0) {
            m = m / 17;
            a[i] = 17;
            i++;
        } else if (m % 13 == 0) {
            m = m / 13;
            a[i] = 13;
            i++;
        } else if (m % 8 == 0) {
            m = m / 8;
            a[i] = 8;
            i++;
        } else {
            break;
        }
    }
    return i;
}