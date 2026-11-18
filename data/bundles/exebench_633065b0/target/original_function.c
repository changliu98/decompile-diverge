int read_data(int fd, unsigned char* buf, unsigned int buf_len) {
    if(fd < 0) {
        return -1;
    }

    unsigned int left_len = buf_len;
    unsigned char* p = buf;
    while(left_len > 0) {

        int size = read(fd, p, left_len);
        if(size <= 0) {
            return -1;
        }
        p += size;
        left_len -= size;
    }

    return (buf_len - left_len);
}