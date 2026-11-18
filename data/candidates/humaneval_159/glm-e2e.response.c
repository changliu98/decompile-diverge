void func0(int a, int b, int c, struct Result *res) {
    if (b > c) {
        res->val1 = a + c;
        res->val2 = 0;
    } else {
        res->val1 = a + b;
        res->val2 = c - b;
    }
}