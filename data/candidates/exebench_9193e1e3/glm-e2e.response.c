void clip_coord(int *coord, int min, int max) {
    int val = *coord;
    
    // Equivalent to: if (val < min) val = min;
    if (val < min) {
        val = min;
    }
    
    // Equivalent to: if (val > max) val = max;
    if (val > max) {
        val = max;
    }
    
    *coord = val;
}