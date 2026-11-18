int CalcOffsetAndShift(int x, int y, long *offset, long *shift) {
    if (x < 0 || x >= 0x54 || y < 0 || y >= 0x30) {
        return -1;
    }
    
    if (offset == 0 || shift == 0) {
        return -1;
    }
    
    int temp = x;
    int div = y / 8;
    
    *offset = (long)(temp + div * 0x54);
    *shift = (long)(y % 8);
    
    return 0;
}