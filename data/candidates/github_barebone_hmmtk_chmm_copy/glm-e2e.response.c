void chmm_copy(struct chmm *src, struct chmm *dst) {
    int i, j;

    dst->N = src->N;
    dst->c = cvector(1, dst->N);
    for (i = 1; i <= dst->N; i++) {
        dst->c[i] = src->c[i];
    }

    dst->M = src->M;
    dst->d = cvector(1, dst->M);
    for (i = 1; i <= dst->M; i++) {
        dst->d[i] = src->d[i];
    }

    dst->A = dmatrix(1, dst->N, 1, dst->N);
    for (i = 1; i <= dst->N; i++) {
        for (j = 1; j <= dst->N; j++) {
            dst->A[i][j] = src->A[i][j];
        }
    }

    dst->B = dmatrix(1, dst->N, 1, dst->M);
    dst->B_1 = dmatrix(1, dst->N, 1, dst->M);
    dst->B_2 = dmatrix(1, dst->N, 1, dst->M);
    for (i = 1; i <= dst->N; i++) {
        for (j = 1; j <= dst->M; j++) {
            dst->B[i][j] = src->B[i][j];
            dst->B_1[i][j] = src->B_1[i][j];
            dst->B_2[i][j] = src->B_2[i][j];
        }
    }

    dst->pi = dvector(1, dst->N);
    for (i = 1; i <= dst->N; i++) {
        dst->pi[i] = src->pi[i];
    }
}