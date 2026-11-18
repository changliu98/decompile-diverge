int mean3(int a, int b, int c, int white, int *err)
{
    int mean = (a + b + c) / 3;
    if (err) {
        int max_err = ((a - mean) > (b - mean) ? (a - mean) : (b - mean));
        max_err = ((max_err) > (c - mean) ? (max_err) : (c - mean));
        *err = max_err;
    }
    if (a < white || b < white || c < white)
        return ((mean) > (white) ? (mean) : (white));
    return mean;
}