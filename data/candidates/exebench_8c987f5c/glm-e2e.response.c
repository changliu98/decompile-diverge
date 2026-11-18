const char* minimum_size_type(int32_t min, uint32_t max, int32_t* size) {
    const char* type = "int32_t";
    int sz = 4;

    if (min >= 0) {
        if (max <= 0xff) {
            type = "uint8_t";
            sz = 1;
        } else if (max < 0xffff) {
            type = "uint16_t";
            sz = 2;
        } else {
            type = "uint32_t";
            sz = 4;
        }
    } else {
        if (min >= -0x7f && max <= 0x7f) {
            type = "int8_t";
            sz = 1;
        } else if (min >= -0x7fff && max < 0x7fff) {
            type = "int16_t";
            sz = 2;
        }
    }

    if (size != NULL) {
        *size = sz;
    }

    return type;
}