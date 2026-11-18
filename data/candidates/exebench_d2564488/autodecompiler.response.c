void multiplyByConstant(int matrix[3][3], int scalar) {
    int row, column;

    for (row = 0; row < 3; ++row) {
        for (column = 0; column < 3; ++column) {
            matrix[row][column] *= scalar;
        }
    }
}