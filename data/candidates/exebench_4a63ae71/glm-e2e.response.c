Assuming the matrix is a 4x4 array of floats
void mtxLoadIdentity(float *mtx) {
    // Set the diagonal elements to 1.0f
    mtx[0]  = 1.0f; // Offset 0x00
    mtx[5]  = 1.0f; // Offset 0x14
    mtx[10] = 1.0f; // Offset 0x28
    mtx[15] = 1.0f; // Offset 0x3c

    // Set the off-diagonal elements to 0.0f
    mtx[1]  = 0.0f; // Offset 0x04
    mtx[2]  = 0.0f; // Offset 0x08
    mtx[3]  = 0.0f; // Offset 0x0c
    mtx[4]  = 0.0f; // Offset 0x10
    mtx[6]  = 0.0f; // Offset 0x18
    mtx[7]  = 0.0f; // Offset 0x1c
    mtx[8]  = 0.0f; // Offset 0x20
    mtx[9]  = 0.0f; // Offset 0x24
    mtx[11] = 0.0f; // Offset 0x2c
    mtx[12] = 0.0f; // Offset 0x30
    mtx[13] = 0.0f; // Offset 0x34
    mtx[14] = 0.0f; // Offset 0x38
}