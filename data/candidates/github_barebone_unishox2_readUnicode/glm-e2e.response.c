define USH_XCODE_EOF 0x7fffff63

int readUnicode(void *arg1, int *arg2, int arg3) {
    int var_20;
    int var_2c;
    int var_24;
    int var_28;
    int var_30;
    
    var_20 = func_0(arg1, arg3, arg2, 5);
    
    if (var_20 == 0x63) {
        return USH_XCODE_EOF;
    }
    
    if (var_20 == 5) {
        var_20 = func_0(arg1, arg3, arg2, 4);
        return var_20 + 0x7fffff00;
    }
    
    if (var_20 < 0) {
        return 0;
    }
    
    if (*arg2 < arg3) {
        var_2c = func_1(arg1, *arg2);
    } else {
        var_2c = 0;
    }
    var_24 = var_2c;
    
    (*arg2)++;
    
    if (*arg2 + ush_len[var_20] - 1 < arg3) {
        return USH_XCODE_EOF;
    }
    
    var_28 = func_0(arg1, arg3, arg2, ush_len[var_20]);
    var_28 += ush_state[var_20];
    
    *arg2 += ush_vcode[var_20];
    
    if (var_24 == 0) {
        var_30 = var_28;
    } else {
        var_30 = -var_28;
    }
    
    return var_30;
}