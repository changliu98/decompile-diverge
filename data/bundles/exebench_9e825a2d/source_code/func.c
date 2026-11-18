
static int C_Utils_compare_float_ptr(const float *item1, const float *item2) { float i1 = *item1; float i2 = *item2; if(i1 == i2) return 0; return i1 < i2 ? -1 : 1; }
