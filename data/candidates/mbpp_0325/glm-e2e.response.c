int func0(int n) {
    if (n <= 3) {
        return n;
    }
    int res = n;
    for (int i = 1; i * i <= n; i++) {
        int temp = res;
        int sub_res = func0(n - i * i) + 1;
        if (temp < sub_res) {
            res = temp;
        } else {
            res = sub_res;
        }
    }
    return res;
}