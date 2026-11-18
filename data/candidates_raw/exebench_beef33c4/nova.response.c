struct Fraction func0(struct Fraction a, struct Fraction b) {
    struct Fraction f;
    f.numerator = (a.numerator * b.denominator);
    f.denominator = (a.denominator * b.numerator);
    return f;
}