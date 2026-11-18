int key_binary_search(node *n, key_t key) {
  key_t *keys = (key_t *)(n + 1);
  int nkeys, l, r;
  if (is_leaf(n))
    nkeys = n->num_keys;
  else
    nkeys = n->num_keys - 1;
  l = -1;
  r = nkeys;
  while (l + 1 < r) {
    int m = l + (r - l) / 2;
    if (keys[m] < key)
      l = m;
    else
      r = m;
  }
  if (r < nkeys && keys[r] == key)
    return r;
  else
    return -r - 1;
}