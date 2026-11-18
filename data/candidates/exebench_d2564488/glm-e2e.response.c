void multiplyByConstant(int arr[3][3], int constant) {
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            arr[i][j] = constant * arr[i][j];
        }
    }
}