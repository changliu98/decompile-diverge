int key_binary_search(struct bplus_node *node, int key)
{
  int i;
  int *keys = (int *)node->children;
  int children;
  if (is_leaf(node))
    children = ((struct bplus_leaf *)node)->children;
  else
    children = ((struct bplus_node *)node)->children - 1;
  int low = -1;
  int high = children;
  while (low + 1 < high)
  {
    int mid = (high - low) / 2 + low;
    if (keys[mid] < key)
      low = mid;
    else
      high = mid;
  }
  if (high < children && keys[high] == key)
    return high;
  else
    return -high - 1;
}