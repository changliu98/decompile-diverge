int SCALE(long long a, int b, int c) {
    int result;
    
    if (a < 0) {
        result = (a * b - c / 2) / c;
    } else {
        result = (a * b + c / 2) / c;
    }
    
    return result;
}