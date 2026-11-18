int** func0(int** matrix, int matrixRowSize, int* matrixColSizes, int x, int* returnSize)
{
    int i, j;
    int **results = (int **)malloc(100 * sizeof(int *));
    int count = 0;
    for (i = 0; i < matrixRowSize; i++)
    {
        for (j = matrixColSizes[i] - 1; j >= 0; j--)
        {
            if (matrix[i][j] == x)
            {
                results[count] = (int *)malloc(2 * sizeof(int));
                results[count][0] = i;
                results[count][1] = j;
                count++;
            }
        }
    }
    *returnSize = count;
    return results;
}