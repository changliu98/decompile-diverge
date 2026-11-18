double estLog(double x) {
    double result = 0.0;
    double i = 1.0;

    while (x > i) {
        result += 1.0;
        i *= 2.0;
    }

    return result;
}