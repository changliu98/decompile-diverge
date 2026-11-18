float get_near_num(float var, float *ptr1, float *ptr2) {
    float ret;
    if ((uintptr_t)ptr1 < (uintptr_t)ptr2) {
        *ptr2 = *ptr1;
        ret = var;
    }
    return ret;
}