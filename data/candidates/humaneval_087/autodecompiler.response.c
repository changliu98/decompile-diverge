int** func0(int** matrix, int matrixRowSize, int *matrixColSizes, int target, int* returnSize) {
    int **ret = (int **)malloc(sizeof(int *) * 100);
    int i, j, k = 0;
    for (i = 0; i < matrixRowSize; i++) {
        for (j = matrixColSizes[i] - 1; j >= 0; j--) {
            if (target == matrix[i][j]) {
                ret[k] = (int *)malloc(sizeof(int) * 2);
                ret[k][0] = i;
                ret[k][1] = j;
                k++;
            }
        }
    }
    *returnSize = k;
    return ret;
}