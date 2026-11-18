static
size_t nrt_testing_atomic_inc(size_t *ptr){

    size_t out = *ptr;
    out += 1;
    *ptr = out;
    return out;
}