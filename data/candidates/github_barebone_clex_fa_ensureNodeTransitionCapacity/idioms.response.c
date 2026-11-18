static _Bool ensureNodeTransitionCapacity(struct clexNode *node, unsigned long required)
{
  if (!node)
    return 0;
  if (node->transitionCapacity >= required)
    return 1;
  if (node->transitionCapacity == 0)
    node->transitionCapacity = 4;
  else
    node->transitionCapacity *= 2;
  while (node->transitionCapacity < required)
  {
    if (node->transitionCapacity > (18446744073709551615UL))
    {
      node->transitionCapacity = required;
      break;
    }
    node->transitionCapacity *= 2;
  }
  struct clexTransition **new = clex_alloc(node->transitions,
    node->transitionCapacity * sizeof(clexTransition));
  if (!new)
    return 0;
  memset(&new[node->transitionCapacity], 0,
    (node->transitionCapacity * sizeof(clexTransition)) -
    (node->transitionCapacity * sizeof(clexTransition)));
  node->transitions = new;
  return 1;
}