int bkm_scale(long long *val, int scale) {
    long long scaled = *val * (long long)scale;
    long long original = *val;
    
    // Check for overflow by dividing the result back by the scale factor
    if (original != scaled / (long long)scale) {
        return 1;
    }
    
    *val = scaled;
    return 0;
}