int mv78xx0_mbus_win_cfg_offset(int arg) {
    int offset;
    
    if (arg < 8) {
        offset = arg << 4;
    } else {
        offset = ((arg - 8) << 4) + 0x900;
    }
    
    return offset;
}