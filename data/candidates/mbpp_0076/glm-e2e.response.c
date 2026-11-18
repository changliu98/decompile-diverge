int func0(int a, int b) {
    if (b < a) {
        int temp = a;
        a = b;
        b = temp;
    }
    // Now a = min(a,b), b = max(a,b)
    
    int result1 = a * (a + 1) * (2 * a + 1) / 6;  // sum of squares: 1²+2²+...+a²
    int result2 = (b - a) * a * (a + 1) / 2;       // (b-a) * triangular number
    
    return result1 + result2;
}