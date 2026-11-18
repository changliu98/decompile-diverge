int func0(double a, double b, double c, double *x) {
    int flag;
    if ((c == a && c!= b) || (c == b && c!= a) || (b == a && b!= c)) {
        flag = 0;
    } else {
        if (a == c) {
            *x = b - a;
        } else if (b == c) {
            *x = a - b;
        } else {
            *x = (c - a) / (b - a);
        }
        flag = 1;
    }
    return flag;
}