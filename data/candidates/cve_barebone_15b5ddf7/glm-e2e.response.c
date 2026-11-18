void libxsmm_sparse_csc_reader(const char *filename, unsigned int *nnz, unsigned int *rows, unsigned int **row_idx, unsigned int **col_idx, double **values) {
    char line[512];
    unsigned int l_nnz = 0;
    unsigned int l_rows = 0;
    unsigned int l_cols = 0;
    unsigned int *l_col_idx = NULL;
    unsigned int *l_row_idx = NULL;
    double *l_values = NULL;
    unsigned int *flag_array = NULL;
    int header_parsed = 0;
    unsigned int i = 0;

    FILE *f = fopen(filename, "r");
    if (f == NULL) {
        return;
    }

    while (fgets(line, 512, f) != NULL) {
        if (strlen(line) == 512) {
            // Line too long, cleanup and return
            free(*row_idx);
            free(*col_idx);
            free(*values);
            free(l_col_idx);
            *row_idx = NULL;
            *col_idx = NULL;
            *values = NULL;
            fclose(f);
            return;
        }

        if (line[0] == '%') {
            continue;
        }

        if (header_parsed == 0) {
            if (sscanf(line, "%u %u %u", &l_rows, &l_cols, &l_nnz) != 3) {
                fclose(f);
                return;
            }

            *row_idx = (unsigned int *)malloc(l_nnz * sizeof(unsigned int));
            *col_idx = (unsigned int *)malloc((l_cols + 1) * sizeof(unsigned int));
            *values = (double *)malloc(l_nnz * sizeof(double));
            l_col_idx = (unsigned int *)malloc(l_cols * sizeof(unsigned int));

            if (*row_idx == NULL || *col_idx == NULL || *values == NULL || l_col_idx == NULL) {
                free(*row_idx);
                free(*col_idx);
                free(*values);
                free(l_col_idx);
                *row_idx = NULL;
                *col_idx = NULL;
                *values = NULL;
                fclose(f);
                return;
            }

            memset(*row_idx, 0, l_nnz * sizeof(unsigned int));
            memset(*col_idx, 0, (l_cols + 1) * sizeof(unsigned int));
            memset(*values, 0, l_nnz * sizeof(double));
            memset(l_col_idx, 0, l_cols * sizeof(unsigned int));

            i = 0;
            while (i <= l_cols) {
                (*col_idx)[i] = l_nnz;
                i++;
            }
            (*col_idx)[0] = 0;
            i = 0;
            header_parsed = 1;
        } else {
            unsigned int r, c;
            double v = 0.0;

            if (sscanf(line, "%u %u %lf", &r, &c, &v) != 3) {
                free(*row_idx);
                free(*col_idx);
                free(*values);
                free(l_col_idx);
                *row_idx = NULL;
                *col_idx = NULL;
                *values = NULL;
                fclose(f);
                return;
            }

            r--;
            c--;

            (*row_idx)[i] = r;
            (*values)[i] = v;
            i++;
            l_col_idx[c] = 1;
            (*col_idx)[c + 1] = i;
        }
    }

    fclose(f);

    if (i != l_nnz) {
        free(*row_idx);
        free(*col_idx);
        free(*values);
        free(l_col_idx);
        *row_idx = NULL;
        *col_idx = NULL;
        *values = NULL;
        return;
    }

    if (l_col_idx != NULL) {
        for (i = 0; i < l_cols; i++) {
            if (l_col_idx[i] == 0) {
                (*col_idx)[i + 1] = (*col_idx)[i];
            }
        }
        free(l_col_idx);
    }
}