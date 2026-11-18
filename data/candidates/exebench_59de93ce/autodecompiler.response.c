void rotr(int *a, int *b, int *c) {
    int tmp = *a;
    *a = *c;
    *c = *b;
    *b = tmp;
}