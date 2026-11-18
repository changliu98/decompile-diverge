void stb_kdtree_search_knn(void *in_root, void *in_point, int in_k, int *in_indices, double *in_distances, int in_dim)
{
    struct stb_kdtree_node *root = (struct stb_kdtree_node *)in_root;
    struct stb_kdtree_point *point = (struct stb_kdtree_point *)in_point;
    int k = in_k;
    int *indices = in_indices;
    double *distances = in_distances;
    int dim = in_dim;
    if (!root)
        return;
    double dist = stb_kdtree_distance_squared(root->point, point, dim);
    int insert_pos = -1;
    for (int i = 0; i < k; ++i)
    {
        if (distances[i] < 0 || distances[i] > dist)
        {
            insert_pos = i;
            break;
        }
    }
    if (insert_pos >= 0)
    {
        for (int i = k - 1; i >= insert_pos; --i)
        {
            distances[i] = distances[i - 1];
            indices[i] = indices[i - 1];
        }
        distances[insert_pos] = dist;
        indices[insert_pos] = root->index;
    }
    double diff = point->point[root->axis] - root->point[root->axis];
    struct stb_kdtree_node *left = (diff < 0) ? root->left : root->right;
    struct stb_kdtree_node *right = (diff < 0) ? root->right : root->left;
    stb_kdtree_search_knn_recursive(right, point, k, indices, distances, dim);
    if (distances[k - 1] < 0 || distances[k - 1] > diff * diff)
        stb_kdtree_search_knn_recursive(left, point, k, indices, distances, dim);
}