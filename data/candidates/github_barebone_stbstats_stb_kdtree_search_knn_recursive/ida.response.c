void __cdecl stb_kdtree_search_knn_recursive(
        stb_kdtree_node *node,
        double *point,
        int k,
        int *indices,
        double *distances,
        int dim)
{
  stb_kdtree_node *left; // [rsp+0h] [rbp-70h]
  stb_kdtree_node *right; // [rsp+8h] [rbp-68h]
  double diff; // [rsp+20h] [rbp-50h]
  int i_0; // [rsp+2Ch] [rbp-44h]
  int i; // [rsp+30h] [rbp-40h]
  int insert_pos; // [rsp+34h] [rbp-3Ch]
  double dist; // [rsp+38h] [rbp-38h]

  if ( node )
  {
    dist = stb_kdtree_distance_squared(node->point, point, dim);
    insert_pos = -1;
    for ( i = 0; i < k; ++i )
    {
      if ( distances[i] < 0.0 || distances[i] > dist )
      {
        insert_pos = i;
        break;
      }
    }
    if ( insert_pos >= 0 )
    {
      for ( i_0 = k - 1; i_0 > insert_pos; --i_0 )
      {
        distances[i_0] = distances[i_0 - 1];
        indices[i_0] = indices[i_0 - 1];
      }
      distances[insert_pos] = dist;
      indices[insert_pos] = node->index;
    }
    diff = point[node->axis] - node->point[node->axis];
    if ( diff >= 0.0 )
      right = node->right;
    else
      right = node->left;
    if ( diff >= 0.0 )
      left = node->left;
    else
      left = node->right;
    stb_kdtree_search_knn_recursive(right, point, k, indices, distances, dim);
    if ( distances[k - 1] < 0.0 || distances[k - 1] > diff * diff )
      stb_kdtree_search_knn_recursive(left, point, k, indices, distances, dim);
  }
}