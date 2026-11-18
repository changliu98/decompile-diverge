int func0(int n) {
    int i = 2;
    int result;

    while (i * i <= n) {
        if (n % i == 0) {
            result = n / i;
            return result;
        }
        i++;
    }
    
    result = 1;
    return result;
}