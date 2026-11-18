int func0(int n) {
    int sum_squares = 0;
    int sum = 0;
    int i = 1;
    
    while (i <= n) {
        sum_squares += i * i;
        sum += i;
        i++;
    }
    
    sum = sum * sum;
    return sum - sum_squares;
}