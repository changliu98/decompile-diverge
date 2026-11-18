int byte_row_gbk1(int c) {
    int result;
    if (c >= 0x81 && c < 0xff) {
        result = c - 0x81;
    } else {
        result = -1;
    }
    return result;
}