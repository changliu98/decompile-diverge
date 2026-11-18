long nrt_testing_atomic_inc(long *ptr) {
    long temp = *ptr;
    temp += 1;
    *ptr = temp;
    return temp;
}