void image_fit(int a, int b, int c, int d, int *x, int *y, char *op) {
    float f_a = (float)a;
    float f_b = (float)b;
    float f_c = (float)c;
    float f_d = (float)d;
    float f_x, f_y;

    f_x = f_a / f_b;
    f_y = f_c / f_d;

    if (((*op) < 1) || ((*op) > 2))
        (*op) = 2;

    if ((*op) == 1) {
        (*y) = (int)(f_x * f_c);
        (*x) = c;
    } else {
        (*x) = (int)(f_y * f_a);
        (*y) = d;
    }
}