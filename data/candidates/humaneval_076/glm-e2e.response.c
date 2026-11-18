bool func0(int a, int b) {
    int result = 1;
    int count = 0;
    
    while (result <= a && count < 100) {
        if (result == a) {
            return true;
        }
        result *= b;
        count++;
    }
    
    return false;
}