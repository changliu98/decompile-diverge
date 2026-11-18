int func0(int a, int b) {
    int c = (a / b) * b;
    int d = c + b;
    int e = a - c;
    int f = d - a;
    
    if (e > f) {
        return d;
    } else {
        return c;
    }
}