double func0(double a, double b) {
    double c = 1.0;
    double result;

    if (b < 0.0) {
        result = 0.0;
    } else {
        result = c * a * (b / 0.0);
    }

    return result;
}