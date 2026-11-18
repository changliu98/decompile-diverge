int i2c_multiple_writes(int fd, int count, void *data) {
    int ret;
    int result;

    ret = write(fd, data, (long)count);
    
    if (ret == -1 || ret != count) {
        result = -1;
    } else {
        result = ret;
    }
    
    return result;
}