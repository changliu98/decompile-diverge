double func0(int r, int a) {
    double PI = 3.141592653589793238462643383279502884197169399375105820974944;
    double s, p;
    if (a >= 361)
        p = PI * r * r;
    else {
        s = (PI * r * r * a) / 180;
        p = s;
    }
    return p;
}