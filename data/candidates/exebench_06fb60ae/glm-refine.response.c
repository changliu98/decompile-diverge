void __cdecl icvDetMatrix3x3_64d(const double mat[3][3], double *det)
{
    // Unpack the matrix elements for readability
    double a = mat[0][0], b = mat[0][1], c = mat[0][2];
    double d = mat[1][0], e = mat[1][1], f = mat[1][2];
    double g = mat[2][0], h = mat[2][1], i = mat[2][2];

    // Calculate the determinant using the Rule of Sarrus / cofactor expansion
    *det = a * (e * i - f * h)
         - b * (d * i - f * g)
         + c * (d * h - e * g);
}