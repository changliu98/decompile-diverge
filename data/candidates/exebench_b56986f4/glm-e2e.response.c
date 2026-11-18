void makeipt(int n, int *a) {
    a[2] = 0;
    a[3] = 16;
    int m = 2;
    int k = n;
    
    while (k > 32) {
        int m2 = m * 2;
        int m2_8 = m2 * 8;
        
        for (int i = m; i < m2; i++) {
            int val = a[i] * 4;
            a[m + i] = val;
            a[m2 + i] = val + m2_8;
        }
        
        m = m2;
        k = k / 4;
    }
}