int clip_f15(int x) {
    int result;
    
    if (x < -0x7FFF) {
        result = -0x7FFF;
    } else {
        int temp;
        if (x > 0x7FFF) {
            temp = 0x7FFF;
        } else {
            temp = x;
        }
        result = temp;
    }
    
    return result;
}