void dhmm_copy(struct dhmm *src, struct dhmm *dst) {
    dst->N = src->N;
    dst->A = cvector(dst->N);
    for (int i = 1; i <= dst->N; i++) {
        dst->A[i] = src->A[i];
    }

    dst->M = src->M;
    dst->B = cvector(dst->M);
    for (int i = 1; i <= dst->M; i++) {
        dst->B[i] = src->B[i];
    }

    dst->pi = dmatrix(dst->N, dst->N);
    for (int i = 1; i <= dst->N; i++) {
        for (int j = 1; j <= dst->N; j++) {
            dst->pi[i][j] = src->pi[i][j];
        }
    }

    dst->b = dmatrix(dst->N, dst->M);
    for (int i = 1; i <= dst->N; i++) {
        for (int j = 1; j <= dst->M; j++) {
            dst->b[i][j] = src->b[i][j];
        }
    }

    dst->alpha = dvector(dst->N);
    for (int i = 1; i <= dst->N; i++) {
        dst->alpha[i] = src->alpha[i];
    }
}