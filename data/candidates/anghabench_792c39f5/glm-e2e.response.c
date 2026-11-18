int check_need_swap(int data_encoding) {
    int endian = 1;
    int *ptr = &endian;
    int host_encoding;
    
    if (*ptr == 1) {
        host_encoding = ELFDATA2LSB;
    } else {
        host_encoding = ELFDATA2MSB;
    }
    
    return host_encoding != data_encoding;
}