int par_msquares_argb(const unsigned char *bytes, int n) {
    int result = 0;
    
    if (n == 4) {
        result |= bytes[2];
        result |= bytes[1] << 8;
        result |= bytes[0] << 16;
        result |= bytes[3] << 24;
    } else {
        for (int i = 0; i < n; i++) {
            result = (result << 8) | bytes[i];
        }
    }
    
    return result;
}