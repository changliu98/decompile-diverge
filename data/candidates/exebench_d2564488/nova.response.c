void multiplyByConstant(int matrix[][COLS], int scalar) {
    int i, j;

    for (i = 0; i < ROWS; i++)
        for (j = 0; j < COLS; j++)
            matrix[i][j] *= scalar;
}