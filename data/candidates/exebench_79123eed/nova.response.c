void quant_u_dec(int a, float *b, float c, float d) {
    float e = (d - c) / (d - 1);
    *b = a * e + c;
}