double estLog(double x) {
    double result = 0.0;
    double current = 2.0;

    while (x > current) {
        result += 1.0;
        current *= 2.0;
    }

    return result;
}