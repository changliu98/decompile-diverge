void atomic_retain(EJDBBSON obj) {
    ((volatile int32_t*)obj)[-1]++;
}