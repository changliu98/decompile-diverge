double func0(int arg0, int arg1) {
    double var1;
    double var2;
    double var3;

    if (arg0 < 0 || arg1 < 0) {
        var1 = -1.0;
    } else {
        var3 = sqrt(2.0) * 2.0;
        var2 = var3 * pow((double)arg0, 3.0);
        var1 = var2 / (double)(arg1 * 4);
    }
    return var1;
}