int cond_read_lock(int *ptr) {
    if (*ptr >= 0) {
        *ptr += 1;
        return 1;
    } else {
        return 0;
    }
}