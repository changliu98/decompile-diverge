int func0(int n) {
    int result;
    
    if (n % 2 != 0) {
        // n is odd
        result = (n + 1) / 2;
    } else {
        // n is even
        int popcount = 0;
        for (int i = 0; i < 32; i++) {
            popcount += (n >> i) & 1;
        }
        
        result = n / 2;
        if (popcount % 2 != 0) {
            result = result + 1;
        }
    }
    
    return result;
}