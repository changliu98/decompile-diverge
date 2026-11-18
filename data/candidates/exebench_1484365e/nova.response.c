int atomic32_increment(int *ptr) {
    int val = ++*ptr;
    return val;
}