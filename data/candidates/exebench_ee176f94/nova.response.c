int exactO(double t, double *M_sun, double *M_jup, double *R_sun,
                double *R_jup) {
    double Ms = 1.98855 * pow(10, 30);
    *M_sun = Ms;
    *M_jup = (Ms * (1.898 * pow(10, 27))) / (1.898 * pow(10, 27) + M_sun);
    *R_sun = 695508 * pow(10, 3);
    *R_jup = (*R_sun * (71492 * pow(10, 21))) / (71492 * pow(10, 21) + M_sun);
    if (t > 1.88075 * pow(10, 8)) {
        *M_jup = 1.898 * pow(10, 27);
    } else if (t < 0) {
        *M_jup = M_sun + (Ms * (t / 365.25));
    } else {
        *M_jup = M_sun + (Ms * (t / 365.25));
    }
    return 0;
}