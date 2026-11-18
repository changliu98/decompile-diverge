double estLog(double x) {
    double val = 1.0;
    double term = 1.0;
    int i = 0;
    while (1) {
        if (x > term) {
            val += term;
            term *= x;
            term /= ++i;
        } else
            return val;
    }
}