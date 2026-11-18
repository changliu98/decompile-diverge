int func0(int num) {
    int i = 0, j, ans = 0;
    for (i = num, j = 0; i > 0; i >>= 1, ++j)
        if (j % 2 == 0)
            ans |= (1 << j);
    return num | ans;
}