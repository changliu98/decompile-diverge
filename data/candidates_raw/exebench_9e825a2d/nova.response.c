int func0(const void *a, const void *b) {
    float a1 = *(float *)a;
    float b1 = *(float *)b;
    int ret;
    if (a1 == b1)
        ret = 0;
    else if (a1 > b1)
        ret = 1;
    else
        ret = -1;
    return ret;
}