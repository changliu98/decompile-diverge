void stb_kdtree_search_knn_recursive(stb_kdtree_node *root, double *pos, int k, int *list, double *dist, int dim)
{
   if (root) {
      double dist2 = stb_kdtree_distance_squared(root->pos, pos, dim);
      int z, insert_pos=-1;
      for (z=0; z < k; ++z) {
         if (dist2 < dist[z]) {
            insert_pos = z;
            break;
         }
      }
      if (insert_pos >= 0) {
         for (z=k-1; z > insert_pos; --z) {
            dist[z] = dist[z-1];
            list[z] = list[z-1];
         }
         dist[insert_pos] = dist2;
         list[insert_pos] = root->data;
      }

      {
         stb_kdtree_node *other, *near;
         double delta = pos[root->axis] - root->pos[root->axis];
         if (delta < 0) {
            near = root->left;
            other = root->right;
         } else {
            near = root->right;
            other = root->left;
         }
         stb_kdtree_search_knn_recursive(near, pos, k, list, dist, dim);
         if (dist[k-1] > delta*delta)
            stb_kdtree_search_knn_recursive(other, pos, k, list, dist, dim);
      }
   }
}