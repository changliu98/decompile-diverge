int byte_col_big5(int c) {
    int col;
    
    if (c >= 0x40 && c < 0x7f) {
        col = c - 0x40;
    } else if (c >= 0xa1 && c < 0xff) {
        col = c - 0x62;
    } else {
        col = -1; // 0xffffffff
    }
    
    return col;
}