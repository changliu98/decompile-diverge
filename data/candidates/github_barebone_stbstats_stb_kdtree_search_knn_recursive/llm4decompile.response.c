void stb_kdtree_search_knn_recursive(stb_kdtree_node *node, double *target, int k, int *indices, double *distances, int dim)
{
   double dist, dx;
   int insert_pos, i;

   if (node == NULL) return;

   dist = stb_kdtree_distance_squared(node->point, target, dim);

   insert_pos = -1;
   for (i=0; i < k; ++i)
      if (distances[i] < 0 || dist < distances[i]) {
         insert_pos = i;
         break;
      }

   if (insert_pos >= 0) {
      for (i=k-1; i > insert_pos; --i) {
         distances[i] = distances[i-1];
         indices[i] = indices[i-1];
      }
      distances[insert_pos] = dist;
      indices[insert_pos] = node->index;
   }

   dx = target[node->axis] - node->point[node->axis];
   if (dx < 0) {
      stb_kdtree_search_knn_recursive(node->left, target, k, indices, distances, dim);
      if (dx*dx < distances[k-1])
         stb_kdtree_search_knn_recursive(node->right, target, k, indices, distances, dim);
   } else {
      stb_kdtree_search_knn_recursive(node->right, target, k, indices, distances, dim);
      if (dx*dx < distances[k-1])
         stb_kdtree_search_knn_recursive(node->left, target, k, indices, distances, dim);
   }
}