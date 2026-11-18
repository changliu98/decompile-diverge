int paeth_predictor(int a, int b, int c) {
    int p = a + b - c;
    int pa = (p > a) ? (p - a) : (a - p);
    int pb = (p > b) ? (p - b) : (b - p);
    int pc = (p > c) ? (p - c) : (c - p);
    
    if (pa <= pb && pa <= pc) {
        return a;
    } else if (pb <= pc) {
        return b;
    } else {
        return c;
    }
}