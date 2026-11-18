void __cdecl stb_qnorm_matrix(STB_MAT *original)
{
    STB_MAT *transposed = NULL;
    STB_MAT *sorted = NULL;
    double var; // Unused besides being passed by reference to stb_meanvar
    double *means;
    int **idx;
    int **ranks;
    int **counts;

    // 1. Transpose the original matrix so columns become rows for easier processing
    stb_transpose_matrix(original, &transposed);

    // 2. Allocate arrays of pointers to hold sorting indices, ranks, and tie counts for each original column
    idx = (int **)malloc(8LL * original->columns);
    counts = (int **)malloc(8LL * original->columns);
    ranks = (int **)malloc(8LL * original->columns);

    // 3. Compute the index, rank, and count arrays for each transposed row (original column)
    for (int i = 0; i < transposed->rows; ++i)
        stb_didx(transposed->data[i], &idx[i], &ranks[i], &counts[i], transposed->columns);

    // 4. Allocate array to store the mean of each sorted rank across all columns
    means = (double *)malloc(8LL * original->rows);

    // 5. Transpose back to get a sorted matrix based on the original dimensions
    stb_transpose_matrix(transposed, &sorted);
    stb_free_matrix(transposed);

    // 6. Calculate the mean for each row in the sorted matrix
    for (int i = 0; i < sorted->rows; ++i)
        stb_meanvar(sorted->data[i], sorted->columns, &means[i], &var);

    stb_free_matrix(sorted);

    // 7. Quantile normalization: replace original values with the computed means based on their rank
    for (int col = 0; col < original->columns; ++col)
    {
        for (int row = 0; row < original->rows; ++row)
        {
            original->data[idx[col][row]][col] = 0.0;
            
            int rank = ranks[col][row];
            int tie_count = counts[col][rank];
            
            // Sum the means for all elements sharing the same rank (handling ties)
            for (int j = 0; j < tie_count; ++j)
            {
                original->data[idx[col][row]][col] += means[j + rank];
            }
            
            // Divide by the number of ties to get the average mean
            original->data[idx[col][row]][col] /= (double)tie_count;
        }
    }

    // 8. Cleanup dynamically allocated memory
    for (int i = 0; i < original->columns; ++i)
    {
        free(idx[i]);
        free(ranks[i]);
        free(counts[i]);
    }
    
    free(idx);
    free(ranks);
    free(counts);
    free(means);
}