void stb_qnorm_matrix(Matrix *m) {
    Matrix transposed;
    Matrix transposed_back;
    double *mean_buf;
    double *val_buf;
    int **rank_buf;
    double *var_buf; // Used to store mean and variance from stb_meanvar
    int i, j, k;

    // Transpose the input matrix
    transposed.data = NULL;
    stb_transpose_matrix(m, &transposed);

    // Allocate buffers for ranks, values, and means
    rank_buf = (int **)malloc(m->cols * sizeof(int *));
    val_buf = (double *)malloc(m->cols * sizeof(double));
    mean_buf = (double *)malloc(m->cols * sizeof(double));

    // Compute ranks for each row (originally columns of the input matrix)
    for (i = 0; i < transposed.rows; i++) {
        stb_didx(transposed.data[i], &rank_buf[i], &val_buf[i], &mean_buf[i], transposed.cols);
    }

    // Allocate buffer for mean/variance results
    var_buf = (double *)malloc(m->rows * sizeof(double));

    // Transpose back to original orientation
    transposed_back.data = NULL;
    stb_transpose_matrix(&transposed, &transposed_back);
    stb_free_matrix(&transposed);

    // Calculate the mean for each row in the transposed-back matrix
    for (i = 0; i < transposed_back.rows; i++) {
        stb_meanvar(transposed_back.data[i], transposed_back.cols, &var_buf[i]);
    }

    stb_free_matrix(&transposed_back);

    // Quantile normalization interpolation
    for (i = 0; i < m->cols; i++) {
        for (j = 0; j < m->rows; j++) {
            int rank = rank_buf[i][j];
            m->data[rank][i] = 0.0;

            // Sum the means for tied ranks
            for (k = 0; k < mean_buf[i][j]; k++) {
                m->data[rank][i] += var_buf[k + (int)val_buf[i][j]];
            }

            // Divide by the number of tied ranks
            m->data[rank][i] /= mean_buf[i][j];
        }
    }

    // Free allocated buffers
    for (i = 0; i < m->cols; i++) {
        free(rank_buf[i]);
        free(val_buf[i]); // Note: val_buf was cast to double* but used as int* in stb_didx
        free(mean_buf[i]);
    }
    free(rank_buf);
    free(val_buf);
    free(mean_buf);
    free(var_buf);
}