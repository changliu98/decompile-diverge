double func0(double x) {
    double temp1 = sqrt(5.0 / 3.0);
    double temp2 = sqrt((2.0 * temp1 + 5.0 / 3.0) * (5.0 / 3.0));
    double volume = (pow(x, 3.0) * temp2) / 3.0;
    return volume;
}