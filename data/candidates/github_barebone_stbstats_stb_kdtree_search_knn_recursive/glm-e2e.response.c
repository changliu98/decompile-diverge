void stb_kdtree_search_knn_recursive(
    struct stb_kdtree_node *node,
    float *target,
    int k,
    int *result_ids,
    double *result_dist_sq,
    int dims
) {
    if (node == NULL) {
        return;
    }

    double dist_sq = stb_kdtree_distance_squared(node->point, target, dims);
    int insert_pos = -1;

    // Find the insertion position in the sorted distance array
    for (int i = 0; i < k; i++) {
        if (result_dist_sq[i] < 0.0 || dist_sq < result_dist_sq[i]) {
            insert_pos = i;
            break;
        }
    }

    // If a valid insertion position is found, shift elements to make space
    if (insert_pos >= 0) {
        for (int i = k - 1; i > insert_pos; i--) {
            result_dist_sq[i] = result_dist_sq[i - 1];
            result_ids[i] = result_ids[i - 1];
        }
        result_dist_sq[insert_pos] = dist_sq;
        result_ids[insert_pos] = node->id;
    }

    // Calculate the distance from the target to the splitting plane
    double diff = target[node->axis] - node->point[node->axis];

    // Determine which subtree is closer and which is farther
    struct stb_kdtree_node *near_child;
    struct stb_kdtree_node *far_child;

    if (diff > 0.0) {
        near_child = node->right;
        far_child = node->left;
    } else {
        near_child = node->left;
        far_child = node->right;
    }

    // Recursively search the nearer subtree
    stb_kdtree_search_knn_recursive(near_child, target, k, result_ids, result_dist_sq, dims);

    // Check if we need to search the farther subtree
    // If the distance to the splitting plane squared is less than the current k-th nearest distance
    if (result_dist_sq[k - 1] < 0.0 || diff * diff < result_dist_sq[k - 1]) {
        stb_kdtree_search_knn_recursive(far_child, target, k, result_ids, result_dist_sq, dims);
    }
}