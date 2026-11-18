int float_to_int32(float f, long *i) {
    *i = (long)(f + 40.0);
    return 1;
}