int func0(int a, int b) {
    int root_b = (int)sqrt((double)b);
    int root_a_minus_1 = (int)sqrt((double)(a - 1));
    return root_b - root_a_minus_1;
}