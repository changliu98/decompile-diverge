int func0(int n) {
    int result;
    if (n == 1) {
        result = 1;
    } else {
        int temp = n;
        int middle_bits = set_middle_bits(n);
        result = temp ^ middle_bits;
    }
    return result;
}