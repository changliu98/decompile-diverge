int mmeq(float *a, float *b, size_t u, size_t v) {
    int i;
    char equal;

    for (i = 0; i < u * v; i++)
        if (a[i]!= b[i]) {
            equal = 0;
            break;
        } else
            equal = 1;

    return equal & 1;
}