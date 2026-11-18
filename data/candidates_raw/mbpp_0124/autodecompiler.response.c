double arg(double x, double y) {
 _Complex c;
 c = x + y * 1.0i;
 return __builtin_carg(c);
}