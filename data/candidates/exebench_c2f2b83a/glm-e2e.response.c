void a_inc(int *ptr) {
    __sync_fetch_and_add(ptr, 1);
}