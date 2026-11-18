void decode6(long long a1, long long a2, long long a3, long long *a4, long long *a5) {
    long long v1 = 6;
    long long v2 = a1 / (a3 * 6);
    long long v3 = (a2 - 4) / 6;
    
    if (v2 >= v3) {
        v2 = v3;
        v1 = a2 - v3 * 6;
    }
    
    long long v4 = a1 - v2 * a3 * 6;
    
    *a4 = v2 * 6 + v4 / v1;
    *a5 = a3 - 1 - v4 / v1;
}