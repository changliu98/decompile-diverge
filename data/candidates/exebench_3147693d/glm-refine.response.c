size_t __cdecl nrt_testing_atomic_inc(size_t *ptr)
{
    *ptr += 1;
    return *ptr;
}