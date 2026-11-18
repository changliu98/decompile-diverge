int clip_wh(int *pos, int *len, int min, int max) {
    int diff;
    
    if (*pos < min) {
        diff = min - *pos;
        *len += *pos;
        *pos = min;
        return diff;
    } else if (*pos + *len >= max) {
        *len = max - *pos;
    }
    
    return 0;
}