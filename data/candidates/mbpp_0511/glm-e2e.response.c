int func0(int n) {
    int sum = 0;
    int i = 2;
    
    while (i * i <= n) {
        while (n % i == 0) {
            sum += i;
            n /= i;
        }
        i++;
    }
    
    sum += n;
    return sum;
}