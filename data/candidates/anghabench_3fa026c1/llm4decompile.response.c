int rdbEncodeInteger(long long value, unsigned char *enc) {
    if (value >= -128 && value <= 127) {
        enc[0] = RDB_ENCVAL<<6 | RDB_ENC_INT8;
        enc[1] = value & 0xff;
        return 2;
    } else if (value >= -32768 && value <= 32767) {
        enc[0] = RDB_ENCVAL<<6 | RDB_ENC_INT16;
        enc[1] = value & 0xff;
        enc[2] = value>>8 & 0xff;
        return 3;
    } else if (value >= -8388608 && value <= 8388607) {
        enc[0] = RDB_ENCVAL<<6 | RDB_ENC_INT32;
        enc[1] = value & 0xff;
        enc[2] = value>>8 & 0xff;
        enc[3] = value>>16 & 0xff;
        enc[4] = value>>24 & 0xff;
        return 5;
    } else {
        return 0;
    }
}