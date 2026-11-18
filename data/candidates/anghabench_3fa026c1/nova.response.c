static int rdbEncodeInteger(long val, char *bf) {
    int rc;

    if (val >= -128 && val < 128) {
        bf[0] = (byte) (val & 0xff);
        rc = 1;
    } else if (val >= -32768 && val < 32768) {
        bf[0] = (byte) (((val >> 8) & 0xff) | LONG_NEG_HIBIT);
        bf[1] = (byte) (val & 0xff);
        rc = 2;
    } else if (val >= -2147483648 && val < 2147483648) {
        bf[0] = (byte) (((val >> 16) & 0xff) | LONG_NEG_HIBIT);
        bf[1] = (byte) (val & 0xff);
        bf[2] = (byte) ((val >> 8) & 0xff);
        rc = 3;
    } else {
        rc = 0;
    }

    return rc;
}