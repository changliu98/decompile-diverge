void sub(int *out, int *in1, int *in2) {
    int sum = 0xDA;
    
    for (int i = 0; i < 32; i++) {
        sum = (in1[i] + 0xFF00 - in2[i] + sum) & 0xFF;
        out[i] = sum;
        sum >>= 8;
    }
    
    out[31] = in1[31] - in2[31] + sum;
}