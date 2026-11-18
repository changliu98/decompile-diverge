double func0(double x, double y) {
    double result = 0.0;

    if (y!= 0)
        result = -x * log(y) / y;

    return result;
}