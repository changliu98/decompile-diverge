void mtxLoadTranslate(float *mtx, float x, float y, float z) {
    // Initialize the main diagonal to 1.0f
    mtx[0]  = 1.0f; // Offset 0x00
    mtx[5]  = 1.0f; // Offset 0x14
    mtx[10] = 1.0f; // Offset 0x28
    mtx[15] = 1.0f; // Offset 0x3c

    // Initialize all other elements to 0.0f
    mtx[1]  = 0.0f; // Offset 0x04
    mtx[2]  = 0.0f; // Offset 0x08
    mtx[3]  = 0.0f; // Offset 0x0c
    mtx[4]  = 0.0f; // Offset 0x10
    mtx[6]  = 0.0f; // Offset 0x18
    mtx[7]  = 0.0f; // Offset 0x1c
    mtx[8]  = 0.0f; // Offset 0x20
    mtx[9]  = 0.0f; // Offset 0x24
    mtx[11] = 0.0f; // Offset 0x2c
    mtx[12] = 0.0f; // Offset 0x30 (Will be overwritten by x)
    mtx[13] = 0.0f; // Offset 0x34 (Will be overwritten by y)
    mtx[14] = 0.0f; // Offset 0x38 (Will be overwritten by z)

    // Set the translation values
    mtx[12] = x;    // Offset 0x30
    mtx[13] = y;    // Offset 0x34
    mtx[14] = z;    // Offset 0x38
}