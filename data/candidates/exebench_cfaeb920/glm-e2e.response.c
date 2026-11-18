void mtxTranspose(float *dst, const float *src) {
    // The matrix is 4x4 floats, so each row is 16 bytes (0x10).
    // Offsets correspond to elements [row][col] as (row * 16 + col * 4).
    
    // Diagonal elements remain in the same position
    dst[0]  = src[0];   // 0x00 -> 0x00
    dst[5]  = src[5];   // 0x14 -> 0x14
    dst[10] = src[10];  // 0x28 -> 0x28
    dst[15] = src[15];  // 0x3c -> 0x3c

    // Swap off-diagonal elements
    dst[4]  = src[1];   // 0x10 -> 0x04
    dst[1]  = src[4];   // 0x04 -> 0x10

    dst[8]  = src[2];   // 0x20 -> 0x08
    dst[2]  = src[8];   // 0x08 -> 0x20

    dst[12] = src[3];   // 0x30 -> 0x0c
    dst[3]  = src[12];  // 0x0c -> 0x30

    dst[9]  = src[6];   // 0x24 -> 0x18
    dst[6]  = src[9];   // 0x18 -> 0x24

    dst[13] = src[7];   // 0x34 -> 0x1c
    dst[7]  = src[13];  // 0x1c -> 0x34

    dst[14] = src[11];  // 0x38 -> 0x2c
    dst[11] = src[14];  // 0x2c -> 0x38
}