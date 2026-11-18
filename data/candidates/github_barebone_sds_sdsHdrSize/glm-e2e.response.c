int sdsHdrSize(unsigned char type) {
    int flags = type & 0x7;
    switch (flags) {
        case 0:
            return 1;
        case 1:
            return 3;
        case 2:
            return 5;
        case 3:
            return 9;
        case 4:
            return 17;
        default:
            return 0;
    }
}