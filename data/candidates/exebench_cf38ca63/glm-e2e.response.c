void bitsToIp4AddrArr(unsigned int ip_bits, unsigned int *arr) {
    arr[0] = (ip_bits & 0xff000000) >> 24;
    arr[1] = (ip_bits & 0x00ff0000) >> 16;
    arr[2] = (ip_bits & 0x0000ff00) >> 8;
    arr[3] = ip_bits & 0x000000ff;
}