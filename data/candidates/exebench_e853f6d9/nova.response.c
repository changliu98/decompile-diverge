int summe(int *a, int *b) {
    int c = *a? 1 : 0;
    *b += *a;
    *a -= 1;
    c = summe(a, b)? 1 : 0;
    return c % 2;
}