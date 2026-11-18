double func0(double x) {
    double result;
    if (x == 0.0) {
        result = 0.0;
    } else {
        double y = x / 2.0;
        double prev_y = 1.0 + y;
        while (y != prev_y) {
            prev_y = y;
            y = (y + x / y) / 2.0;
        }
        result = y;
    }
    return result;
}