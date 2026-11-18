void func0(struct Fraction *fr, double a, double b) {
    double temp = (fr->numerator * b) + (fr->denominator * a);
    fr->numerator = (fr->numerator * a);
    fr->denominator = (fr->denominator * b);
    fr->numerator = temp;
}