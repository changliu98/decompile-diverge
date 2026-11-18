int func0(int n) {
    int original_n = n;
    int count = 0;
    int i = 2;
    
    while (i * i <= original_n) {
        int exp = 0;
        while (n % i == 0) {
            n /= i;
            exp++;
        }
        
        int sum = 0;
        int term = 1;
        while (sum + term <= exp) {
            sum += term;
            count++;
            term++;
        }
        
        i++;
    }
    
    if (n != 1) {
        count++;
    }
    
    return count;
}