void icvDetMatrix3x3_64d(double mat[3][3], double *det) {
    double a = mat[0][0] * (mat[1][1] * mat[2][2] - mat[1][2] * mat[2][1]);
    double b = mat[0][1] * (mat[1][2] * mat[2][0] - mat[1][0] * mat[2][2]);
    double c = mat[0][2] * (mat[1][0] * mat[2][1] - mat[1][1] * mat[2][0]);
    *det = a + b + c;
}