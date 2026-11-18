void warp_mat4_fill_transpose(float *dst, const float *src) {
    // Assuming a 4x4 matrix represented as a 1D array of 16 floats.
    // The function transposes the matrix from src into dst.
    
    // Row 0 of dst = Column 0 of src
    dst[0]  = src[0];
    dst[1]  = src[4];
    dst[2]  = src[8];
    dst[3]  = src[12];

    // Row 1 of dst = Column 1 of src
    dst[4]  = src[1];
    dst[5]  = src[5];
    dst[6]  = src[9];
    dst[7]  = src[13];

    // Row 2 of dst = Column 2 of src
    dst[8]  = src[2];
    dst[9]  = src[6];
    dst[10] = src[10];
    dst[11] = src[14];

    // Row 3 of dst = Column 3 of src
    dst[12] = src[3];
    dst[13] = src[7];
    dst[14] = src[11];
    dst[15] = src[15];
}