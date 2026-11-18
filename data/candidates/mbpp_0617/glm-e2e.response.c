int func0(int a, int b, int c) {
    int max_ab = a;
    if (a < b) {
        max_ab = b;
    }
    a = max_ab;

    int min_ab = a;
    if (a > b) {
        min_ab = b;
    }
    b = min_ab;

    int result;
    if (c >= b) {
        result = (c + b - 1) / b;
    } else if (c == 0) {
        result = 0;
    } else if (c == a) {
        result = 1;
    } else {
        result = 2;
    }
    
    return result;
}