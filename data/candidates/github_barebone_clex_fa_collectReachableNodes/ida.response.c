bool __cdecl collectReachableNodes(clexNode *start, NodeVec *nodes)
{
  size_t j; // [rsp+0h] [rbp-30h]
  clexNode *node; // [rsp+8h] [rbp-28h]
  size_t i; // [rsp+10h] [rbp-20h]

  if ( !start || !nodes )
    return 0;
  if ( !nodeVecPush(nodes, start) )
    return 0;
  for ( i = 0LL; i < nodes->size; ++i )
  {
    node = nodes->items[i];
    for ( j = 0LL; j < node->transitionCount; ++j )
    {
      if ( node->transitions[j]
        && node->transitions[j]->to
        && !nodeVecContains(nodes, node->transitions[j]->to)
        && !nodeVecPush(nodes, node->transitions[j]->to) )
      {
        return 0;
      }
    }
  }
  return 1;
}