void swapminusfloat( double *a, double *b ) {
  *a -= *b;
  *b += *a;
  *a = (*b - *a);
}