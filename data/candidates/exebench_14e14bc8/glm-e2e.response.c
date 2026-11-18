void c_sysconf_(int *name, long *value, int *errnum) {
    *value = sysconf(*name);
    *errnum = errno;
}