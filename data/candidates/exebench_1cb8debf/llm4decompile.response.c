void sBitwiseXor_process(sBitwiseXor_t *me, float bIn0, float bIn1, float *bOut)
{
    int a = (int) bIn0;
    int b = (int) bIn1;
    *bOut = (float) (a ^ b);
}