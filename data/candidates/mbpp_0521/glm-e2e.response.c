bool func0(int a, int b, int c) {
    bool result;
    
    if (a == b || b == c || c == a) {
        result = false;
    } else {
        result = true;
    }
    
    return result;
}