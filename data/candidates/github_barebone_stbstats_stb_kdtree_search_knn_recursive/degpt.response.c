void stb_kdtree_search_knn_recursive
               (stb_kdtree_node *node,double *point,int k,int *indices,double *distances,int dim)

{
  stb_kdtree_node *node_00;
  int iVar1;
  double dVar2;
  stb_kdtree_node *local_78;
  stb_kdtree_node *far;
  stb_kdtree_node *near;
  double diff;
  int i_1;
  int i;
  int insert_pos;
  double dist;
  int dim_local;
  double *distances_local;
  int *indices_local;
  int k_local;
  double *point_local;
  stb_kdtree_node *node_local;
  
  if (node != (stb_kdtree_node *)0x0) {
    dVar2 = stb_kdtree_distance_squared(node->point,point,dim);
    insert_pos = -1;
    for (i = 0; i < k; i = i + 1) {
      if ((distances[i] <= 0.0 && distances[i] != 0.0) || (dVar2 < distances[i])) {
        insert_pos = i;
        break;
      }
    }
    iVar1 = k;
    if (-1 < insert_pos) {
      while (i_1 = iVar1 + -1, insert_pos < i_1) {
        distances[i_1] = distances[iVar1 + -2];
        indices[i_1] = indices[iVar1 + -2];
        iVar1 = i_1;
      }
      distances[insert_pos] = dVar2;
      indices[insert_pos] = node->index;
    }
    dVar2 = point[node->axis] - node->point[node->axis];
    if (0.0 <= dVar2) {
      node_00 = node->right;
      local_78 = node->left;
    }
    else {
      node_00 = node->left;
      local_78 = node->right;
    }
    stb_kdtree_search_knn_recursive(node_00,point,k,indices,distances,dim);
    if ((distances[k + -1] <= 0.0 && distances[k + -1] != 0.0) ||
       (dVar2 * dVar2 < distances[k + -1])) {
      stb_kdtree_search_knn_recursive(local_78,point,k,indices,distances,dim);
    }
  }
  return;
}