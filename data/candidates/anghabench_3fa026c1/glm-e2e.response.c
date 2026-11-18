int rdbEncodeInteger(long value, unsigned char *p) {
    if (value >= -128 && value <= 127) {
        p[0] = (RDB_ENCVAL << 6) | RDB_ENC_INT8;
        p[1] = value & 0xFF;
        return 2;
    } else if (value >= -32768 && value <= 32767) {
        p[0] = (RDB_ENCVAL << 6) | RDB_ENC_INT16;
        p[1] = value & 0xFF;
        p[2] = (value >> 8) & 0xFF;
        return 3;
    } else if (value >= -2147483648LL && value <= 2147483647LL) {
        p[0] = (RDB_ENCVAL << 6) | RDB_ENC_INT32;
        p[1] = value & 0xFF;
        p[2] = (value >> 8) & 0xFF;
        p[3] = (value >> 16) & 0xFF;
        p[4] = (value >> 24) & 0xFF;
        return 5;
    } else {
        return 0;
    }
}