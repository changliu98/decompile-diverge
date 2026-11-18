int byte_row_johab_hangul(int arg) {
    int result;
    
    if (arg >= 0x84 && arg < 0xd4) {
        result = arg - 0x84;
    } else {
        result = -1;
    }
    
    return result;
}