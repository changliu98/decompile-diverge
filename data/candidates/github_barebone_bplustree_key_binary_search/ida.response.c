int __cdecl key_binary_search(bplus_node *node, key_t target)
{
  int children; // [rsp+Ch] [rbp-34h]
  int high; // [rsp+14h] [rbp-2Ch]
  int low; // [rsp+18h] [rbp-28h]
  key_t *arr; // [rsp+20h] [rbp-20h]

  arr = (key_t *)&node[1];
  if ( is_leaf(node) )
    children = node->children;
  else
    children = node->children - 1;
  low = -1;
  high = children;
  while ( low + 1 < high )
  {
    if ( target <= arr[(high - low) / 2 + low] )
      high = (high - low) / 2 + low;
    else
      low += (high - low) / 2;
  }
  if ( high < children && arr[high] == target )
    return high;
  else
    return -high - 1;
}