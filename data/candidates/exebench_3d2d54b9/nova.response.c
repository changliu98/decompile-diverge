int foo(int i, int *p) {
    if (i!= 9)
        p[0] = 0;
    else
        p[1] = 0;
    return 3;
}