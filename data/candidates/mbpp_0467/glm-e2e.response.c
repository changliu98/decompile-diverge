int func0(int n) {
    int result = 0;
    int multiplier = 1;
    
    while (n != 0) {
        int remainder = n % 8;
        result += remainder * multiplier;
        multiplier *= 10;
        n /= 8;
    }
    
    return result;
}