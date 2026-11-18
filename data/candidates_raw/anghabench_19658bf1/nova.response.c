int func0(int offset) {
    int ret = buffer[offset];
    ip = offset + ip;
    return ret;
}