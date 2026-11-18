void clearZeroflag(void *ptr) {
    *((char *)ptr + 6) = '0';
}