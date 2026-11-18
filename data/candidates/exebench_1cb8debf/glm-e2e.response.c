void sBitwiseXor_process(float a, float b, float *out) {
    int int_a = (int)a;
    int int_b = (int)b;
    *out = (float)(int_a ^ int_b);
}