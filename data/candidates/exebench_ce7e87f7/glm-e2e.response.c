void BGBBTJ_BC7_EncodeBlock_VecSwapRGBA(uint32_t *a, uint32_t *b) {
    uint32_t temp;
    
    // Swap element 0
    temp = a[0];
    a[0] = b[0];
    b[0] = temp;
    
    // Swap element 1
    temp = a[1];
    a[1] = b[1];
    b[1] = temp;
    
    // Swap element 2
    temp = a[2];
    a[2] = b[2];
    b[2] = temp;
    
    // Swap element 3
    temp = a[3];
    a[3] = b[3];
    b[3] = temp;
}