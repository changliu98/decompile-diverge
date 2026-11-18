void index_to_xwy(int a, int b, int *q, int *r) {
    *r = a % b;
    *q = a / b;
}