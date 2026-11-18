void DFT2(float *A, float *sinTab)
{
    float tmp0, tmp1;

    tmp0 = A[0] - A[1];
    tmp1 = A[0] + A[1];
    A[0] = tmp1;
    A[1] = tmp0;
}