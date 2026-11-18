int func0(int n) {
    int ans = 0;
    int i = n;
    while (i > 0) {
        if (i & (i - 1) == 0) {
            ans = i;
            break;
        } else {
            i = i - 1;
        }
    }
    return ans;
}