void bitrv208(double f[2][2]) {
    double temp[2][2];
    for (int i = 0; i < 2; i++) {
        for (int j = 0; j < 2; j++) {
            temp[i][j] = f[i][j];
        }
    }
    for (int i = 0; i < 2; i++) {
        for (int j = 0; j < 2; j++) {
            f[i][j] = temp[j][1 - i];
        }
    }
}