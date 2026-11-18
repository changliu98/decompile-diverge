int rfftp_forward(struct SOM som, double *input_vector,
                        unsigned int vector_dims) {
    unsigned int i, j, bmu_index, n_nodes = som.n_nodes;
    double *node_vect, *bmu_vect;
    double bmu_dist, dist;

    if (som.n_nodes == 1)
        bmu_index = 0;
    else {
        bmu_vect = (double *)malloc(n_nodes * sizeof(double));
        if (bmu_vect == NULL)
            return -1;

        for (i = 0; i < n_nodes; i++) {
            node_vect = som.data[i];
            bmu_dist = euclidean_distance(node_vect, input_vector,
                                          vector_dims);
            if (i == 0) {
                bmu_vect = node_vect;
                bmu_index = i;
                bmu_dist = dist;
            } else if (dist < bmu_dist) {
                bmu_vect = node_vect;
                bmu_index = i;
                bmu_dist = dist;
            }
        }
    }

    for (i = 0; i < n_nodes; i++) {
        for (j = 0; j < n_nodes; j++) {
            if (i == j)
                continue;

            dist = euclidean_distance(som.data[i], bmu_vect, vector_dims);
            update_weight(som.data[i], bmu_vect, dist, bmu_index, i, j);
        }
    }

    free(bmu_vect);
    bmu_vect = NULL;
    bmu_index = 0;

    return bmu_index;
}