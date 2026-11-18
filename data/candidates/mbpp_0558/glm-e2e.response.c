int func0(int a, int b) {
    int diff = abs(a - b);
    int sum = 0;
    
    while (diff > 0) {
        sum += diff % 10;
        diff /= 10;
    }
    
    return sum;
}