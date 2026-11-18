int func0(int arg) {
    int var1 = arg / 100;
    int var2 = arg / 400;
    int var3 = arg / 4;
    int var4 = arg - var3;
    
    if (var1 != 0) {
        var4 += var1;
        var3 -= var1;
    }
    
    if (var2 != 0) {
        var4 -= var2;
        var3 += var2;
    }
    
    int var5 = var4 + var3 * 2;
    return var5 % 7;
}