void matM4toM3(double (*dst)[3], double (*src)[4]) {
    dst[0][0] = src[0][0];
    dst[0][1] = src[0][1];
    dst[0][2] = src[0][2];
    
    dst[1][0] = src[1][0];
    dst[1][1] = src[1][1];
    dst[1][2] = src[1][2];
    
    dst[2][0] = src[2][0];
    dst[2][1] = src[2][0]; // Note: Assembly reads 0x40 twice
    dst[2][2] = src[2][2];
}