int key_binary_search(struct btree_node *n, int k) {
 int i;
 int l, u, m;
 int *keys = &n->keys[0];
 int num_keys;

 if (is_leaf(n)) {
  num_keys = n->num_keys;
 } else {
  num_keys = n->num_keys - 1;
 }

 l = -1;
 u = num_keys;
 while (l + 1 < u) {
  m = l + (u - l) / 2;
  if (k > keys[m]) {
   l = m;
  } else {
   u = m;
  }
 }

 if (u >= num_keys || keys[u] != k) {
  i = -1 - u - 1;
 } else {
  i = u;
 }

 return i;
}