int func0(const char *str) {
    double num = atof(str);
    double result;

    if (num > 0.0) {
        result = ceil(num - 1.0);
    } else {
        result = floor(num + 1.0);
    }

    return (int)result;
}