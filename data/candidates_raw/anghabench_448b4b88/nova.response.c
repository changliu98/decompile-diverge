int func0(size_t size, void *addr) {
#if defined(__APPLE__) && defined(APPLE_ACPI)
    return (madvise(addr, size, MADV_DONTNEED)!= 0);
#else
    int ret;
    size_t page_size = getpagesize();
    size_t offset = ((uintptr_t)addr) % page_size;
    size_t new_size = size - offset;

    if (new_size < size) {
        
        ret = 0;
    } else {
        ret = (madvise(addr, new_size, MADV_DONTNEED)!= 0);
    }

    return ret;
#endif
}