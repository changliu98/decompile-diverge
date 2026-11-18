static _Bool collectReachableNodes(struct clexNode *start, struct NodeVec *nodes)
{
  if (start == ((void *)0) || nodes == ((void *)0))
    return 0;
  if (!is_start_valid(nodes, start))
    return 0;
  for (unsigned long i = 0; i < nodes->size; i++) {
    struct clexNode *node = nodes->items[i];
    for (unsigned long j = 0; j < node->transitionCount; j++) {
      if (node->transitions[j] != ((void *)0)
        && node->transitions[j]->to != ((void *)0)) {
        if (!is_end_valid(nodes, node->transitions[j]->to))
          if (!is_start_valid(nodes, node->transitions[j]->to))
            return 0;
      }
    }
  }
  return 1;
}