void multiply(int matrix1[][2], int matrix2[][2]) {
    int temp;
    int a = ((matrix1[0][0] * matrix2[0][0]) + (matrix1[0][1] * matrix2[1][0])) % 100;
    int b = ((matrix1[0][0] * matrix2[0][1]) + (matrix1[0][1] * matrix2[1][1])) % 100;
    int c = ((matrix1[1][0] * matrix2[0][0]) + (matrix1[1][1] * matrix2[1][0])) % 100;
    int d = ((matrix1[1][0] * matrix2[0][1]) + (matrix1[1][1] * matrix2[1][1])) % 100;

    matrix1[0][0] = a;
    matrix1[0][1] = b;
    matrix1[1][0] = c;
    matrix1[1][1] = d;
}