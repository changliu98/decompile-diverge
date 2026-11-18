void dwordstore(void *ptr, int32_t value) {
    ((unsigned char *)ptr)[0] = (value) & 0xFF;
    ((unsigned char *)ptr)[1] = (value >> 8) & 0xFF;
    ((unsigned char *)ptr)[2] = (value >> 16) & 0xFF;
    ((unsigned char *)ptr)[3] = (value >> 24) & 0xFF;
}