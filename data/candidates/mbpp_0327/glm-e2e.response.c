bool func0(int a, int b, int c) {
    bool result;
    
    if (a == b || b == c || c == a) {
        result = true;
    } else {
        result = false;
    }
    
    return result;
}