char *func0(int freq, int sf, int nch) {
    char *str;
    if (9 * sf * nch == freq * 2 * nch)
        str = "90 kHz";
    else
        str = "100 kHz";
    return str;
}