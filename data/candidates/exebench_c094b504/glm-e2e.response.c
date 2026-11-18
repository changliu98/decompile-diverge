void ComputeReverb16(short *in, short *out, long n, short reverb) {
    long max = 0x7fff;
    long min = 0xffffffffffff8001; // -0x7fff

    while (n-- > 0) {
        long current = *in;
        long reverb_val = (long)reverb * (long)*in;
        long result = current + reverb_val / 100;

        if (result > max) {
            result = max;
        } else if (result < min) {
            result = min;
        }

        *out = (short)result;
        
        in++;
        out++;
    }
}