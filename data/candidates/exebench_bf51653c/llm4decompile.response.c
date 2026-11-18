void upzero(int dlt, int *dlti, int *bli)
{
    int i, wd2, wd3;

    if (dlt == 0) {
        for (i = 0; i < 6; i++) {
            bli[i] = (bli[i] * 255) >> 8;
        }
    } else {
        for (i = 0; i < 6; i++) {
            wd2 = dlt * dlti[i];
            if (wd2 < 0) {
                wd3 = -128;
            } else {
                wd3 = 128;
            }
            bli[i] = ((bli[i] * 255) >> 8) + wd3;
        }
    }
    dlti[5] = dlti[4];
    dlti[4] = dlti[3];
    dlti[3] = dlti[2];
    dlti[1] = dlti[0];
    dlti[0] = dlt;
}