int cfftp_comp_twiddle(struct cfftp_plan_t *plan) {
    long n = plan->n;
    double *table = (double *)malloc(n * 2 * sizeof(double));
    if (table == NULL) {
        return -1;
    }

    sincos_2pibyn(n, table);

    long m_prod = 1;
    long offset = 0;

    for (long i = 0; i < plan->nb; i++) {
        long m = plan->bluestein[i].m;
        long m_div = m_prod / m;

        plan->bluestein[i].w1 = plan->twiddle + offset;

        offset += (m - 1) * (m_div - 1);

        for (long j = 1; j < m; j++) {
            for (long k = 1; k < m_div; k++) {
                long idx = (2 * m_prod * j * k) * 2;
                plan->bluestein[i].w1[(j - 1) * (m_div - 1) + (k - 1)] = table[idx];
                plan->bluestein[i].w1[(j - 1) * (m_div - 1) + (k - 1) + 1] = table[idx + 1];
            }
        }

        if (m > 11) {
            plan->bluestein[i].w2 = plan->twiddle + offset;
            offset += m;

            for (long j = 0; j < m; j++) {
                long idx = (2 * m_prod * j * m_div) * 2;
                plan->bluestein[i].w2[j] = table[idx];
                plan->bluestein[i].w2[j + 1] = table[idx + 1];
            }
        }

        m_prod *= m;
    }

    free(table);
    return 0;
}