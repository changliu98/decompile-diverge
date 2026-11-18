int func0(int a, int b) {
    if (b < a) {
        int temp = a;
        a = b;
        b = temp;
    }
    
    int term1 = b * (b + 1);
    int term2 = 3 * a - b + 1;
    int numerator = term1 * term2;
    
    return numerator / 6;
}