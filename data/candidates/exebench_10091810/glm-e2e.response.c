void BGBBTJ_BC7_EncodeBlock_VecSwapRGB(int *a, int *b) {
    int temp;

    // Swap offset 0
    temp = a[0];
    a[0] = b[0];
    b[0] = temp;

    // Swap offset 4
    temp = a[1];
    a[1] = b[1];
    b[1] = temp;

    // Swap offset 8
    temp = a[2];
    a[2] = b[2];
    b[2] = temp;
}