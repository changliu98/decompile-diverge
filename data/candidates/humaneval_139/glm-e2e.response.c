long long func0(int n) {
    long long a = 1;
    long long b = 1;
    int i = 1;
    
    while (i <= n) {
        a = a * i;
        b = b * a;
        i++;
    }
    
    return b;
}