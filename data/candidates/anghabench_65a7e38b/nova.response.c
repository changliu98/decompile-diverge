int SCALE(long long int x, int n, int m) {
    int ans;
    if (x >= 1) {
        long long int temp = x * n;
        ans = (temp - (m / 2)) / m;
    } else {
        long long int temp = x * n;
        ans = (temp + (m / 2)) / m;
    }
    return ans;
}