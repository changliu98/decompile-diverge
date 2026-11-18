int func0(int n) {
    n = n + 1;
    int i = 2;
    int ans = n / 2;
    
    while (i <= n) {
        int q = n / i;
        ans = ans + (q / 2) * i;
        if (q % 2 != 0) {
            ans = ans + (n % i);
        }
        i = i * 2;
    }
    
    return ans;
}