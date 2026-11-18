void func0(Graph *G) {
    int i, j;
    Graph *G_T = NULL;
    Graph *G_R = NULL;
    Graph *G_R_T = NULL;
    Matrix *M = NULL;
    Matrix *M_R = NULL;
    Matrix *M_R_T = NULL;
    Matrix *M_R_T_R = NULL;

    createGraph(G, &G_T);

    M = (Matrix *)malloc(G->vexNum * sizeof(Matrix));
    M_R = (Matrix *)malloc(G->vexNum * sizeof(Matrix));
    M_R_T = (Matrix *)malloc(G->vexNum * sizeof(Matrix));

    for (i = 0; i < G->vexNum; i++) {
        for (j = 0; j < G->vexNum; j++) {
            M[i][j] = G->arcs[i][j];
        }
    }

    transpose(M, M_R, G->vexNum);

    for (i = 0; i < G->vexNum; i++) {
        for (j = 0; j < G->vexNum; j++) {
            M_R[i][j] = M_R[i][j] / G->vexs[j].data;
        }
    }

    transpose(M_R, M_R_T, G->vexNum);

    free(M);
    free(M_R);
    free(M_R_T);
}