bool func0(int a, int b, int c) {
    bool result;
    
    if (a + b > c && a + c > b && b + c > a) {
        result = true;
    } else {
        result = false;
    }
    
    return result;
}