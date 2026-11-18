int __cdecl key_binary_search(bplus_node *node, key_t target)
{
  // In a B+ tree, the keys are stored inline immediately after the node header.
  key_t *keys = (key_t *)&node[1];
  
  // Leaf nodes contain 'children' number of keys.
  // Internal nodes contain 'children - 1' number of keys (as one child pointer lacks a leftward key separator).
  int num_keys = is_leaf(node) ? node->children : node->children - 1;

  int low = -1;
  int high = num_keys;

  // Standard binary search using an open interval (low, high]
  while (low + 1 < high)
  {
    int mid = low + (high - low) / 2; // Overflow-safe midpoint calculation
    
    if (target <= keys[mid])
      high = mid;
    else
      low = mid;
  }

  // If the target is found at the final high index, return the index
  if (high < num_keys && keys[high] == target)
    return high;

  // If not found, return the bitwise negation (or standard insertion index encoding) of 'high'.
  // In many B+ tree implementations, returning -high - 1 indicates the child index 
  // where the target should be inserted or traversed next.
  return -high - 1;
}