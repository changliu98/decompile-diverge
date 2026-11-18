void stb_qnorm_matrix(STB_MAT *original)
{
    STB_MAT *transposed = NULL;
    stb_transpose_matrix(original, &transposed);

    int **ranks = malloc(sizeof(int *) * original->columns);
    int **counts = malloc(sizeof(int *) * original->columns);
    int **idx = malloc(sizeof(int *) * original->columns);

    /* For each row determine a rank from lowest to highest taking into consideration possible ties
     * at the same time, we rearrange that first set of row values so each row is in order going lowest to highest value
     */
    for (int i = 0; i < transposed->rows; i++) {
        stb_didx(transposed->data[i], &idx[i], &ranks[i], &counts[i], transposed->columns);
    }

    /* Now that everything is sorted, we find the mean for each row to determine the value of the ranks (this is for quantile normalization without reference,
     * otherwise it is the reference value)
     */
    double *means = malloc(sizeof(double) * original->rows);
    double var;
    STB_MAT *sorted = NULL;
    stb_transpose_matrix(transposed, &sorted);
    stb_free_matrix(transposed);
    for (int i = 0; i < sorted->rows; i++) {
        stb_meanvar(sorted->data[i], sorted->columns, &means[i], &var);
    }

    stb_free_matrix(sorted);

    // Now take the ranking order and substitute in new values at the original locations. 
    for (int i = 0; i < original->columns; i++) {
        for (int n = 0; n < original->rows; n++) {
            // find the index in the original dataset
            original->data[idx[i][n]][i] = 0.0;
            //Note that when, values are tied in rank, they should instead be assigned the mean of the values.
            for (int j = 0; j < counts[i][ranks[i][n]]; j++) {
                original->data[idx[i][n]][i] += means[ranks[i][n] + j]; 
            }
            original->data[idx[i][n]][i] /=  (double) counts[i][ranks[i][n]];
        }
    }

    // Cleanup
    for (int i = 0; i < original->columns; i++) {
        free(idx[i]);
        free(ranks[i]);
        free(counts[i]);
    }

    free(idx);
    free(ranks);
    free(counts);

    free(means);
}