int checkRecord(int n) {
    int *mods = (int*)malloc(n*sizeof(int));
    int **recs = (int**)malloc((n+1)*sizeof(int*));
    int **recs_t = (int**)malloc((n+1)*sizeof(int*));
    int i, j, k, ret;

    for (i = 0; i <= n; ++i) {
        recs[i] = (int*)calloc(3, sizeof(int));
        recs_t[i] = (int*)calloc(3, sizeof(int));
    }

    recs[0][0] = recs[0][1] = recs[0][2] = 0;
    recs_t[0][0] = recs_t[0][1] = recs_t[0][2] = 0;

    for (i = 1; i <= n; ++i) {
        mods[i-1] = (i * i - i + 1) % 3;

        for (j = 0; j < 3; ++j)
            recs[i][j] = recs[i-1][j];

        recs[i][mods[i-1]] += 1;
    }

    for (k = 1; k <= 2; ++k) {
        for (i = 1; i <= n; ++i) {
            for (j = 0; j < 3; ++j)
                recs_t[i][j] = recs_t[i-1][j];

            if (i > 0)
                for (j = 0; j < 3; ++j)
                    recs_t[i][(j + mods[i-1]) % 3] += recs[i-1][j];
        }

        for (i = 0; i <= n; ++i) {
            for (j = 0; j < 3; ++j) {
                recs[i][j] = recs_t[i][j];
                recs_t[i][j] = 0;
            }
        }
    }

    ret = recs[n][0];

    for (i = 0; i <= n; ++i) {
        free(recs[i]);
        free(recs_t[i]);
    }

    free(recs);
    free(recs_t);
    free(mods);

    return ret;
}