bool __cdecl collectReachableNodes(clexNode *start, NodeVec *nodes)
{
  if (!start || !nodes)
    return false;

  if (!nodeVecPush(nodes, start))
    return false;

  for (size_t i = 0; i < nodes->size; ++i)
  {
    const clexNode *node = nodes->items[i];
    
    for (size_t j = 0; j < node->transitionCount; ++j)
    {
      clexNode *targetNode = node->transitions[j] ? node->transitions[j]->to : nullptr;
      
      if (targetNode && !nodeVecContains(nodes, targetNode))
      {
        if (!nodeVecPush(nodes, targetNode))
          return false;
      }
    }
  }
  
  return true;
}