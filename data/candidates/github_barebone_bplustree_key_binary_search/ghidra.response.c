int key_binary_search(bplus_node *node,key_t target)

{
  int iVar1;
  int iVar2;
  int local_3c;
  int mid;
  int high;
  int low;
  int len;
  key_t *arr;
  key_t target_local;
  bplus_node *node_local;
  int local_c;
  
  iVar1 = is_leaf(node);
  if (iVar1 == 0) {
    local_3c = node->children + -1;
  }
  else {
    local_3c = node->children;
  }
  low = -1;
  high = local_3c;
  iVar1 = high;
  while (high = iVar1, low + 1 < high) {
    iVar2 = low + (high - low) / 2;
    iVar1 = iVar2;
    if (*(int *)((long)&node[1].self + (long)iVar2 * 4) < target) {
      iVar1 = high;
      low = iVar2;
    }
  }
  if ((high < local_3c) && (*(int *)((long)&node[1].self + (long)high * 4) == target)) {
    local_c = high;
  }
  else {
    local_c = -1 - high;
  }
  return local_c;
}