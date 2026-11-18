void dhmm_copy(matrix *m, matrix *n) {
    int i, j, k;
    n->rows = m->rows;
    n->columns = m->columns;
    for (i = 1; i <= n->rows; i++) {
        for (j = 1; j <= n->columns; j++) {
            n->array[i][j] = m->array[i][j];
        }
    }
}