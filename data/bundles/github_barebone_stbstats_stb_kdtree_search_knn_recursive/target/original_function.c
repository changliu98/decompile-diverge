static void stb_kdtree_search_knn_recursive(stb_kdtree_node *node, double *point, int k, 
                                            int *indices, double *distances, int dim) {
    if (node == NULL) return;
    
    double dist = stb_kdtree_distance_squared(node->point, point, dim);
    
    // Check if this point should be in top k
    int insert_pos = -1;
    for (int i = 0; i < k; i++) {
        if (distances[i] < 0 || dist < distances[i]) {
            insert_pos = i;
            break;
        }
    }
    
    if (insert_pos >= 0) {
        // Shift elements and insert
        for (int i = k - 1; i > insert_pos; i--) {
            distances[i] = distances[i - 1];
            indices[i] = indices[i - 1];
        }
        distances[insert_pos] = dist;
        indices[insert_pos] = node->index;
    }
    
    // Determine which side to search first
    double diff = point[node->axis] - node->point[node->axis];
    stb_kdtree_node *near = diff < 0 ? node->left : node->right;
    stb_kdtree_node *far = diff < 0 ? node->right : node->left;
    
    stb_kdtree_search_knn_recursive(near, point, k, indices, distances, dim);
    
    // Check if we need to search the other side
    if (distances[k - 1] < 0 || diff * diff < distances[k - 1]) {
        stb_kdtree_search_knn_recursive(far, point, k, indices, distances, dim);
    }
}