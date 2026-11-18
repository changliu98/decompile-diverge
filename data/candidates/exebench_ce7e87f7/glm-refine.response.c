void __cdecl BGBBTJ_BC7_EncodeBlock_VecSwapRGBA(int *clra, int *clrb)
{
    int tmp;

    // Swap index 0
    tmp = clra[0];
    clra[0] = clrb[0];
    clrb[0] = tmp;

    // Swap index 1
    tmp = clra[1];
    clra[1] = clrb[1];
    clrb[1] = tmp;

    // Swap index 2
    tmp = clra[2];
    clra[2] = clrb[2];
    clrb[2] = tmp;

    // Swap index 3
    tmp = clra[3];
    clra[3] = clrb[3];
    clrb[3] = tmp;
}