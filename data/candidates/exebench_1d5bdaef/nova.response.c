int foo(float *ptr, int size) {
    int res;
    if ((ptr[0] < 0 && ptr[1] > 0) || (ptr[0] < 0 && ptr[1] < 0)) {
        res = size;
    } else {
        res = 0;
    }
    return res;
}