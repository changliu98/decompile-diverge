void func0(struct SOM som, struct Data data) {
    data.rows = som.rows;
    data.cols = som.cols;

    data.weight = (double *)malloc(data.rows * data.cols * sizeof(double));
    for (int i = 0; i < data.rows; i++) {
        data.weight[i] = som.weight[i];
    }

    data.distance = (double *)malloc(data.rows * sizeof(double));
    for (int i = 0; i < data.rows; i++) {
        data.distance[i] = som.distance[i];
    }

    data.neighbor = (int *)malloc(data.rows * sizeof(int));
    for (int i = 0; i < data.rows; i++) {
        data.neighbor[i] = som.neighbor[i];
    }

    data.cluster = (int *)malloc(data.rows * sizeof(int));
    for (int i = 0; i < data.rows; i++) {
        data.cluster[i] = som.cluster[i];
    }

    data.u_matrix = (double *)malloc(data.rows * data.cols * sizeof(double));
    for (int i = 0; i < data.rows; i++) {
        data.u_matrix[i] = som.u_matrix[i];
    }
}