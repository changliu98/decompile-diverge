int func0(char *s) {
    double x = atof(s);
    if (x < 0)
        return ceil(x - 0.5);
    else
        return floor(x + 0.5);
}