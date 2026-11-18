void swap(int *a, int *b, int *c, int *d) {
 if (*c < *a) {
  *c ^= *a;
  *c ^= *b;
  *c ^= *a;
 }
 if (*d < *b) {
  *d ^= *b;
  *d ^= *c;
  *d ^= *b;
 }
}