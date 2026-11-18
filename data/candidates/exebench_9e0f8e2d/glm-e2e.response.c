void h(int *ptr, int val) {
    if (*ptr > val) {
        h(ptr, *ptr);
    } else {
        *ptr = *ptr - val;
    }
}