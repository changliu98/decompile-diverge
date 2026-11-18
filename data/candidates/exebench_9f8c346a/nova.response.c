struct Fraction bn_sqr_comba4(struct Fraction f1, struct Fraction f2) {
    struct Fraction f;
    f.numerator = (f1.numerator * f2.denominator) + (f2.numerator * f1.denominator);
    f.denominator = f1.denominator * f2.denominator;
    return f;
}