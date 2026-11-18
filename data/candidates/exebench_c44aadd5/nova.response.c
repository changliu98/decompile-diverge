float ran2(long *xp) {
    int i;
    long x;
    float y;

    if (*xp <= 0) {
        for (i = 0; i < 39; i++)
            if ((*xp -= x) < 1)
                return (y = (float)x / 52774);
        *xp += 2147483563;
    }
    x = *xp / 52774;
    *xp -= x * 52774;
    if (*xp < 0)
        *xp += 2147483563;
    for (i = 0; i < 32; i++)
        if ((*xp -= x) < 1)
            return (y = (float)x / 52774);
    *xp += 2147483563;
    return (y = (float)x / 52774);
}