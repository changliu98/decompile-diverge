int affs_intl_toupper(int ch) {
    int result;

    if ((ch >= 0x61 && ch <= 0x7a) || 
        (ch >= 0xe0 && ch <= 0xfe && ch != 0xf7)) {
        result = ch - 0x20;
    } else {
        result = ch;
    }
    
    return result;
}