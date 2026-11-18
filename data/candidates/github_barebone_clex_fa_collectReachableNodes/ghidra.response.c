_Bool collectReachableNodes(clexNode *start,NodeVec *nodes)

{
  clexNode *pcVar1;
  _Bool _Var2;
  size_t j;
  clexNode *node;
  size_t i;
  NodeVec *nodes_local;
  clexNode *start_local;
  _Bool local_9;
  
  if ((start == (clexNode *)0x0) || (nodes == (NodeVec *)0x0)) {
    local_9 = false;
  }
  else {
    _Var2 = nodeVecPush(nodes,start);
    if (_Var2) {
      for (i = 0; i < nodes->size; i = i + 1) {
        pcVar1 = nodes->items[i];
        for (j = 0; j < pcVar1->transitionCount; j = j + 1) {
          if ((((pcVar1->transitions[j] != (clexTransition *)0x0) &&
               (pcVar1->transitions[j]->to != (clexNode *)0x0)) &&
              (_Var2 = nodeVecContains(nodes,pcVar1->transitions[j]->to), !_Var2)) &&
             (_Var2 = nodeVecPush(nodes,pcVar1->transitions[j]->to), !_Var2)) {
            return false;
          }
        }
      }
      local_9 = true;
    }
    else {
      local_9 = false;
    }
  }
  return local_9;
}