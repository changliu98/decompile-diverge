void __cdecl denormF(double F[3][3], double *transform1, double *transform2)
{
    // Unpack the second transformation
    double scale2 = transform2[0];
    double trans2_x = transform2[1];
    double trans2_y = transform2[2];

    // Apply translation of transform2 to the third row of F
    F[2][0] += trans2_x * F[0][0] + trans2_y * F[1][0];
    F[2][1] += trans2_x * F[0][1] + trans2_y * F[1][1];
    F[2][2] += trans2_x * F[0][2] + trans2_y * F[1][2];

    // Apply scale of transform2 to the first and second rows of F
    for (int i = 0; i < 2; i++) {
        F[i][0] *= scale2;
        F[i][1] *= scale2;
        F[i][2] *= scale2;
    }

    // Unpack the first transformation
    double scale1 = transform1[0];
    double trans1_x = transform1[1];
    double trans1_y = transform1[2];

    // Apply translation of transform1 to the third column of F
    F[0][2] += trans1_x * F[0][0] + trans1_y * F[0][1];
    F[1][2] += trans1_x * F[1][0] + trans1_y * F[1][1];
    F[2][2] += trans1_x * F[2][0] + trans1_y * F[2][1];

    // Apply scale of transform1 to the first and second columns of F
    for (int i = 0; i < 3; i++) {
        F[i][0] *= scale1;
        F[i][1] *= scale1;
    }
}