double func0(int arg1, int arg2, double arg3) {
    int var1 = arg2;
    int var2 = arg2;
    
    if (var2 > arg1 / 2) {
        arg2 = arg1 - arg2;
    }
    
    double var3 = 1.0;
    for (int i = 1; i <= arg2; i++) {
        var3 *= (double)(arg1 - arg2 + i) / (double)i;
    }
    
    double var4 = var3 * pow(arg3, var1);
    double var5 = (1.0 - arg3) * pow((double)(arg1 - var1), 1.0);
    
    return var4 + var5;
}