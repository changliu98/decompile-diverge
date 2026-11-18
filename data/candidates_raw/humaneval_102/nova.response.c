int func0(int n, int i) {
    int ans;
    if (i < n) {
        ans = -1;
    } else if (i == n) {
        if (i % 2 == 1) {
            ans = -1;
        } else {
            ans = i / 2 - 1;
        }
    } else {
        if (i % 2 == 1) {
            ans = -1;
        } else {
            ans = i / 2;
        }
    }
    return ans;
}