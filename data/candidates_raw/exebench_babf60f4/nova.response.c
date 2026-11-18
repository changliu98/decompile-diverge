void func0(float matriz1[][3], float matriz2[][3], float matrizResultado[][3]) {
    int i, j, k;
    for (i = 0; i < 4; i++) {
        for (j = 0; j < 4; j++) {
            matrizResultado[i][j] = 0;
            for (k = 0; k < 4; k++) {
                matrizResultado[i][j] += matriz1[i][k] * matriz2[k][j];
            }
        }
    }
}