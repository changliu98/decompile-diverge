int sdsHdrSize(sds s) {
    int len;

    switch (s[0] & 0x7) {
        case 0:
            len = 1;
            break;
        case 1:
            len = 3;
            break;
        case 2:
            len = 5;
            break;
        case 3:
            len = 9;
            break;
        case 4:
            len = 17;
            break;
        default:
            len = 0;
            break;
    }
    return len;
}