int func0(int a, int b) {
    int g = ngcd(a, b);
    int count = 0;
    int limit = (int)sqrt((double)g);
    
    for (int i = 1; i <= limit; i++) {
        if (g % i == 0) {
            count += 2;
            if (i == g / i) {
                count--;
            }
        }
    }
    
    return count;
}