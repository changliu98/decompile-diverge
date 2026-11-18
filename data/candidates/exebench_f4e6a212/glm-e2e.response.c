void mix_16h_to_32_s2(int *out, const short *in, int n) {
    n >>= 1;
    while (n--) {
        *out += (int)(*in) >> 1;
        out++;
        in++;
        
        *out += (int)(*in) >> 1;
        out++;
        in++;
        
        in += 6;
    }
}