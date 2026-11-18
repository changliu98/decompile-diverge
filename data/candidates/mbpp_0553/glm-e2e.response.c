float func0(int arg0, int arg1) {
    int var1 = 0;
    int var2 = arg1;
    
    if (var2 == 0) {
        var1 = 1;
    } else {
        while (var2 != 0) {
            var1++;
            var2 /= 10;
        }
    }
    
    double d0 = (double)arg0;
    double d1 = (double)arg1;
    double pow_result = pow((double)var1, 10.0);
    
    return (float)(d0 + d1 / pow_result);
}