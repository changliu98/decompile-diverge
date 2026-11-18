void matrix2r(double *src, double *dst) {
    int i = 0;
    
    // First element
    i++;
    i++;
    i++;
    dst[0] = src[i++];
    
    // Second element
    i++;
    i++;
    i++;
    dst[1] = src[i++];
    
    // Third element
    i++;
    i++;
    i++;
    dst[2] = src[i++];
}