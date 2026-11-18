int obdRevConvert_23(float var, int* out1, int* out2, int* out3) {
    var = var / 100.0f;
    long long val = (long long)var;
    *out1 = val / 256;
    *out2 = val % 256;
    return 2;
}