int OS_file_open(int *fd, const char *pathname) {
    int status;

    *fd = open(pathname, 0);
    
    if (*fd == -1) {
        status = 0x1004;
    } else {
        status = 0;
    }
    
    return status;
}