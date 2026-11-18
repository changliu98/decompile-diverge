unsigned char* ikcp_encode8u(unsigned char *ptr, unsigned char byte) {
    *ptr = byte;
    return ptr + 1;
}