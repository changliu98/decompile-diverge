int func0(int n, int m) {
    int gcd = ngcd(n, m);
    int result = 0;
    int i;
    int z = sqrt(gcd);
    for (i = 1; i <= z; i++) {
        if (gcd % i == 0) {
            result += 2;
            if (i == gcd / i) {
                result--;
            }
        }
    }
    return result;
}