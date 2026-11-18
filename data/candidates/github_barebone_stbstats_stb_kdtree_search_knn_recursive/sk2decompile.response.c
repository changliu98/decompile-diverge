static void stb_kdtree_search_knn_recursive(stb_kdtree_node *n, double *pos,
                                            int k, int *result, double *dist,
                                            int dim) {
  double d, dx;
  int i, insert_at;
  stb_kdtree_node *near_subtree, *far_subtree;
  if (n == NULL) return;
  d = stb_kdtree_distance_squared(n->pos, pos, dim);
  insert_at = -1;
  for (i = 0; i < k; ++i)
    if (dist[i] < 0 || dist[i] > d) {
      insert_at = i;
      break;
    }
  if (insert_at >= 0) {
    for (i = k - 1; i > insert_at; --i) {
      dist[i] = dist[i - 1];
      result[i] = result[i - 1];
    }
    dist[insert_at] = d;
    result[insert_at] = n->value;
  }
  dx = pos[n->split_dim] - n->pos[n->split_dim];
  if (dx < 0) {
    near_subtree = n->left;
    far_subtree = n->right;
  } else {
    near_subtree = n->right;
    far_subtree = n->left;
  }
  stb_kdtree_search_knn_recursive(near_subtree, pos, k, result, dist, dim);
  if (dist[k - 1] < 0 || dx * dx < dist[k - 1])
    stb_kdtree_search_knn_recursive(far_subtree, pos, k, result, dist, dim);
}