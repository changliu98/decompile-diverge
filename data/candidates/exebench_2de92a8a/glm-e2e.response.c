int sprint_int_number_nonlocalized(char *str, int num, int decimals, int show_plus) {
    int flag = 0;
    int idx = 0;
    int divisor = 1000000000;
    
    if (decimals < 0) {
        decimals = 0;
    }
    if (decimals > 9) {
        flag = 1;
    }
    
    if (num < 0) {
        str[idx++] = '-';
        num = -num;
    } else if (show_plus != 0) {
        str[idx++] = '+';
    }
    
    for (int i = 10; i != 0; i--) {
        if (decimals == i) {
            flag = 1;
        }
        
        int digit = num / divisor;
        num %= divisor;
        
        if (digit != 0 || flag != 0) {
            str[idx++] = (char)digit + '0';
            flag = 1;
        }
        
        divisor /= 10;
    }
    
    if (flag == 0) {
        str[idx++] = '0';
    }
    
    str[idx] = '\0';
    
    return idx;
}