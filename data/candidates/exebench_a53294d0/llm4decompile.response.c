int matCopyVdf(const double v[3], float copy[3])
{





    int i;
    for (i = 0; i < 3; i++) {
        copy[i] = (float)v[i];
    }

    return 0;
}