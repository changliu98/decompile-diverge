void __cdecl stb_kdtree_search_knn_recursive(
        stb_kdtree_node *node,
        double *point,
        int k,
        int *indices,
        double *distances,
        int dim)
{
    if (!node)
        return;

    // 1. Calculate squared distance from the target point to the current node's point
    double dist = stb_kdtree_distance_squared(node->point, point, dim);

    // 2. Insert the current node into the k-nearest neighbors arrays if it's closer
    int insert_pos = -1;
    for (int i = 0; i < k; ++i)
    {
        // A negative distance implies an empty slot (infinity)
        if (distances[i] < 0.0 || distances[i] > dist)
        {
            insert_pos = i;
            break;
        }
    }

    if (insert_pos >= 0)
    {
        // Shift elements to the right to make room for the new neighbor
        for (int i = k - 1; i > insert_pos; --i)
        {
            distances[i] = distances[i - 1];
            indices[i] = indices[i - 1];
        }
        distances[insert_pos] = dist;
        indices[insert_pos] = node->index;
    }

    // 3. Determine which subtree is "near" and which is "far" based on the splitting axis
    double diff = point[node->axis] - node->point[node->axis];
    
    stb_kdtree_node *near_child = (diff >= 0.0) ? node->right : node->left;
    stb_kdtree_node *far_child  = (diff >= 0.0) ? node->left  : node->right;

    // 4. Always search the near subtree first
    stb_kdtree_search_knn_recursive(near_child, point, k, indices, distances, dim);

    // 5. Search the far subtree only if it could contain a closer point
    // Check if the splitting plane is closer than the current worst (k-th) neighbor
    double worst_dist = distances[k - 1];
    if (worst_dist < 0.0 || worst_dist > diff * diff)
    {
        stb_kdtree_search_knn_recursive(far_child, point, k, indices, distances, dim);
    }
}