static char func0(short s) {
    int sign, exp, sig, val;
    char res;
    exp = ((s >> 8) & 0xff);
    sig = (s & 0xff);
    sign = (s >> 15) & 0xff;
    if (sign)
        s = -s;
    exp = exp + BIAS;
    val = sig;
    val = val << 3;
    val = val >> 3;
    exp = exp - BIAS;
    exp = exp << 4;
    exp = exp >> 4;
    res = (char)(sign | exp | val);
    return res;
}