void BGBBTJ_BC7_EncodeBlock_VecSwapRGBA(int *a, int *b) {
    int temp;
    temp = *a;
    *a = *b;
    *b = temp;
    temp = *(a + 1);
    *(a + 1) = *(b + 1);
    *(b + 1) = temp;
    temp = *(a + 2);
    *(a + 2) = *(b + 2);
    *(b + 2) = temp;
    temp = *(a + 3);
    *(a + 3) = *(b + 3);
    *(b + 3) = temp;
}