double func0(int arg1, int arg2) {
    double var1 = 0.0; // Loaded from 0x2008
    double var2;

    if (arg2 >= 360) {
        var2 = 0.0; // Loaded from 0x2018
    } else {
        var2 = var1 * (double)arg1 * (double)arg1 * ((double)arg2 / 360.0); // 360.0 loaded from 0x2010
    }

    return var2;
}