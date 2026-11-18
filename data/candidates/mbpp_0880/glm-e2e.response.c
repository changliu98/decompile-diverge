const char* func0(int a, int b, int c) {
    const char* result;
    
    if (b * b - 4 * a * c > 0) {
        result = "More";
    } else if (b * b - 4 * a * c == 0) {
        result = "Equal";
    } else {
        result = "Less";
    }
    
    return result;
}