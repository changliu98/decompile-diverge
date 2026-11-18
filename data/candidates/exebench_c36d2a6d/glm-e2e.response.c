int epindex_to_epnum(int epindex, int *out) {
    int remainder = epindex % 2;
    
    if (out != NULL) {
        *out = remainder;
    }
    
    return (epindex + remainder) / 2;
}