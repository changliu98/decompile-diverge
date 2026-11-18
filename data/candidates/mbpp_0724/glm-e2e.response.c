int func0(int num, int n) {
    int digits[1000];
    int len = 1;
    digits[0] = 1;
    int carry = 0;
    
    for (int i = 0; i < n; i++) {
        carry = 0;
        for (int j = 0; j < len; j++) {
            long long val = (long long)digits[j] * num + carry;
            digits[j] = val % 10;
            carry = val / 10;
        }
        while (carry > 0) {
            digits[len] = carry % 10;
            carry /= 10;
            len++;
        }
    }
    
    int sum = 0;
    for (int i = 0; i < len; i++) {
        sum += digits[i];
    }
    
    return sum;
}