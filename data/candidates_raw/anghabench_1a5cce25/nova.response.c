int func0(long x, long *r) {
    int ok = 0;
    long result = x;
    *r = result;
    switch (result) {
    case 128:
        ok = 1;
        break;
    case 129:
        *r = 128;
        ok = EAGAIN;
        break;
    case 130:
        *r = (long)sysconf(_SC_PAGESIZE);
        ok = EAGAIN;
        break;
    }
    return ok;
}