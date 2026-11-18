double func0(int arg) {
    double pow_result = pow(arg, 2.0);
    double sqrt_result = sqrt(2.0);
    double temp = pow_result / (sqrt_result * 3.0);
    double rounded = round(temp * 100.0) / 100.0;
    return rounded;
}