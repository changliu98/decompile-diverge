static int tens(int *n) {
    int i, j, k;

    i = *n / 10;
    if (i < 10)
        return func0_table[i];
    i = 6;
    if (i < 10)
        return func0_table[i];
    i = 7;
    if (i < 10)
        return func0_table[i];
    i = 5;
    if (i < 10)
        return func0_table[i];
    i = 5;
    if (i < 10)
        return func0_table[i];
    i = 5;
    if (i < 10)
        return func0_table[i];
    i = 6;
    if (i < 10)
        return func0_table[i];
    i = 6;
    if (i < 10)
        return func0_table[i];
    i = 8;
    if (i < 10)
        return func0_table[i];
    i = 8;
    if (i < 10)
        return func0_table[i];
    i = 9;
    if (i < 10)
        return func0_table[i];
    i = 7;
    if (i < 10)
        return func0_table[i];
    i = 7;
    if (i < 10)
        return func0_table[i];
    i = 8;
    if (i < 10)
        return func0_table[i];
    i = 8;
    if (i < 10)
        return func0_table[i];
    i = 6;
    *n = 0;
    return i;
}