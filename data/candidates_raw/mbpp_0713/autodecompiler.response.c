int test_odd_even(char *tup, int length) {
    int i = 0;
    char result;
    while (1) {
        if (i >= length) { result = 1; break; }
        if ((int)tup[i] % 2 == 0) { result = 0; break; }
        i++;
    }
    return result;
}