int func0(float a, float b, float c) {
    // Check if all sides are integers
    if (roundf(a) != a || roundf(b) != b || roundf(c) != c) {
        return 0;
    }
    
    // Check if any two sides sum to the third side
    if (a + b == c || a + c == b || b + c == a) {
        return 1;
    }
    
    return 0;
}