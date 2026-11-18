int atmc_fetch_and_add(int *a, int b) {
    int c = b;
    *a += b;
    b += c;
    return b + c;
}