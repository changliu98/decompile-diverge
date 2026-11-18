double func0(double a, double b, double c, double d) {
    double sin_a = sin(a);
    double sin_c = sin(c);
    double cos_a = cos(a);
    double cos_c = cos(c);
    double cos_a_cos_c = cos_a * cos_c;
    double cos_diff = cos(b - d);
    double arg = sin_a * sin_c + cos_diff * cos_a_cos_c;
    return acos(arg) * 6371.0;
}