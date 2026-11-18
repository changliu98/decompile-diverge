bool __cdecl ensureNodeTransitionCapacity(clexNode *node, size_t required)
{
  size_t transitionCapacity; // [rsp+0h] [rbp-30h]
  clexTransition **resized; // [rsp+8h] [rbp-28h]
  size_t newCapacity; // [rsp+10h] [rbp-20h]

  if ( !node )
    return 0;
  if ( node->transitionCapacity >= required )
    return 1;
  if ( node->transitionCapacity )
    transitionCapacity = node->transitionCapacity;
  else
    transitionCapacity = 4LL;
  for ( newCapacity = transitionCapacity; newCapacity < required; newCapacity *= 2LL )
  {
    if ( newCapacity > 0x7FFFFFFFFFFFFFFFLL )
    {
      newCapacity = required;
      break;
    }
  }
  resized = (clexTransition **)realloc(node->transitions, 8 * newCapacity);
  if ( !resized )
    return 0;
  memset(&resized[node->transitionCapacity], 0, 8 * (newCapacity - node->transitionCapacity));
  node->transitions = resized;
  node->transitionCapacity = newCapacity;
  return 1;
}