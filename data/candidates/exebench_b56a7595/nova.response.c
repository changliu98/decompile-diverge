void rotr(int *a, int *b, int *c) {
    int temp;
    temp = *c;
    *c = *b;
    *b = *a;
    *a = temp;
}