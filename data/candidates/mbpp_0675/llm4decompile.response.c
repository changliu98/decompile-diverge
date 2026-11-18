int func0(int x, int y, int m, int n) {
    int sum_nums;
    sum_nums = x + y;
    if (sum_nums < m) {
        return sum_nums;
    }
    if (sum_nums > n) {
        return sum_nums;
    }
    return 20;
}