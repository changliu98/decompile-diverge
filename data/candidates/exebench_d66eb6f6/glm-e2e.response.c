int bcd2int(unsigned char *bcd, int len) {
    int result;
    if (len > 5) {
        result = 0;
    } else {
        int val = 0;
        for (int i = 0; i < len; i++) {
            val = (val * 100) + ((bcd[i] / 16) * 10) + (bcd[i] % 16);
        }
        result = val;
    }
    return result;
}