int val_seg(int val) {
    int res = 0;
    
    val = val >> 7;
    
    if ((val & 0xf0) != 0) {
        val = val >> 4;
        res = res + 4;
    }
    
    if ((val & 0xc) != 0) {
        val = val >> 2;
        res = res + 2;
    }
    
    if ((val & 0x2) != 0) {
        res = res + 1;
    }
    
    return res;
}