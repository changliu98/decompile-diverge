int foo(float *buf, float threshold)
{
    int mask = 0;
    unsigned int i = 0;

    for (;;) {
        if (i >= 9) break;
        if (buf[i] > threshold) mask |= (1 << i);
        i++;
    }

    return mask;
}