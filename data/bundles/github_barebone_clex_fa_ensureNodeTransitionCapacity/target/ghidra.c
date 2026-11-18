_Bool ensureNodeTransitionCapacity(clexNode *node,size_t required)

{
  size_t sVar1;
  clexTransition **ppcVar2;
  size_t local_38;
  clexTransition **resized;
  size_t newCapacity;
  size_t required_local;
  clexNode *node_local;
  _Bool local_9;
  
  if (node == (clexNode *)0x0) {
    local_9 = false;
  }
  else if (node->transitionCapacity < required) {
    if (node->transitionCapacity == 0) {
      local_38 = 4;
    }
    else {
      local_38 = node->transitionCapacity;
    }
    for (newCapacity = local_38;
        (sVar1 = newCapacity, newCapacity < required &&
        (sVar1 = required, newCapacity < 0x8000000000000000)); newCapacity = newCapacity << 1) {
    }
    newCapacity = sVar1;
    ppcVar2 = realloc(node->transitions,newCapacity << 3);
    if (ppcVar2 == (clexTransition **)0x0) {
      local_9 = false;
    }
    else {
      memset(ppcVar2 + node->transitionCapacity,0,(newCapacity - node->transitionCapacity) * 8);
      node->transitions = ppcVar2;
      node->transitionCapacity = newCapacity;
      local_9 = true;
    }
  }
  else {
    local_9 = true;
  }
  return local_9;
}