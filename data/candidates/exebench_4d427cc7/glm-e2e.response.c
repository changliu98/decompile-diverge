void setIRQflag(char *ptr) {
    ptr[5] = 0x31; // 0x31 is the ASCII character '1'
}