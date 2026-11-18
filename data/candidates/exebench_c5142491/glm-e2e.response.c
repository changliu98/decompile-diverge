int read_data(int fd, char *buf, int size) {
    int total_read = 0;
    int bytes_read;

    while (total_read != size) {
        bytes_read = read(fd, buf + total_read, size - total_read);
        
        if (bytes_read <= 0) {
            return -1;
        }
        
        total_read += bytes_read;
    }
    
    return 0;
}