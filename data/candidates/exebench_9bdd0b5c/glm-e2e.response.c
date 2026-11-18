int foo(int *p) {
    *p = 0xdead;
    return *p;
}