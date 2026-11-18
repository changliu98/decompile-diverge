void matmat3(double a[3][3], double b[3][3], double c[3][3], double alpha, double beta) {
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            c[i][j] = alpha * c[i][j] + beta * (
                a[i][0] * b[0][j] +
                a[i][1] * b[1][j] +
                a[i][2] * b[2][j]
            );
        }
    }
}