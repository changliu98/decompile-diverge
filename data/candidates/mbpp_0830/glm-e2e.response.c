double func0(double value, int digits) {
    double pow_neg_digits = pow(10.0, -digits);
    double temp = ceil(value / pow_neg_digits) * pow_neg_digits;
    double rounded = round(temp * pow(10.0, digits));
    return rounded / pow(10.0, digits);
}