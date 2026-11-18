void mlMatrixLoadTransposedRotation(float *dst, const float *src) {
    // Assuming a 3x3 matrix layout (12 bytes per row if padded to 4 floats, or 9 contiguous floats)
    // The offsets in the assembly (0x0, 0x4, 0x8, 0x10, 0x14, 0x18, 0x20, 0x24, 0x28)
    // indicate a 4-float padded row stride (16 bytes per row).
    
    // Row 0 of destination gets Column 0 of source
    dst[0]  = src[0];
    dst[1]  = src[4];
    dst[2]  = src[8];
    
    // Row 1 of destination gets Column 1 of source
    dst[4]  = src[1];
    dst[5]  = src[5];
    dst[6]  = src[9];
    
    // Row 2 of destination gets Column 2 of source
    dst[8]  = src[2];
    dst[9]  = src[6];
    dst[10] = src[10];
}