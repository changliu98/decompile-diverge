static void matrix2r(const double A[16], double r[3]) {
    enum {X, Y, Z};
    int i;
    i = 0;
    i++; i++; i++; r[X] = A[i++];
    i++; i++; i++; r[Y] = A[i++];
    i++; i++; i++; r[Z] = A[i++];
}