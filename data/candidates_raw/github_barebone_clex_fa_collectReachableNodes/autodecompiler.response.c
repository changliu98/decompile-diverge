static int nodeVecExpand(node_t *node, node_vec_t *vec) {
  size_t i, j;
  node_t *child;
  char ret;

  if (!node || !vec) { ret = 0; goto end; };

  if (!(ret = nodeVecPush(vec, node))) goto end;

  for (i = 0; i < vec->len; i++) {
    child = vec->data[i];
    for (j = 0; j < child->num_children; j++) {
      if (!child->children[j] || !child->children[j]->name ||
          nodeVecContains(vec, child->children[j]->name)) continue;
      if (!(ret = nodeVecPush(vec, child->children[j]->name))) goto end;
    }
  }

  ret = 1;
end:
  return ret;
}