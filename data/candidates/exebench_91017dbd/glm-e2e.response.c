void ddelete_c(const char *pathname, int *errnum) {
    int ret;
    
    if (unlink(pathname) != 0) {
        ret = errno;
    } else {
        ret = 0;
    }
    
    *errnum = ret;
}