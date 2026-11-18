int func0(int a, int b) {
    int sum_b = sum_Odd(b);
    int sum_a_minus_1 = sum_Odd(a - 1);
    return sum_b - sum_a_minus_1;
}