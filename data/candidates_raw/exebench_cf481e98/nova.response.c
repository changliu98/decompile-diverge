void func0(float x, float *f) {
    float y;
    unsigned int ix;
    GET_FLOAT_WORD(ix,x);
    ix &= 0x7fffffff;
    if (ix < 0x3f800000+(1<<23)) {
        if (ix < 0x3f800000) {
            if (ix < 0x3f800000-(1<<23)) {
                *f = 0.0/x;
                return;
            }
        }
        else {
            y = 1.0;
        }
    }
    else {
        y = 0.0;
    }
    *f = y*expf(x*x*0.5f + x*0.5f + C1 + C2);
}