void clexNfaDestroyInternal(clexNode *nfa,NodeVec *seen)

{
  _Bool _Var1;
  size_t i;
  NodeVec *seen_local;
  clexNode *nfa_local;
  
  if (((nfa != (clexNode *)0x0) && (_Var1 = nodeVecContains(seen,nfa), !_Var1)) &&
     (_Var1 = nodeVecPush(seen,nfa), _Var1)) {
    for (i = 0; i < nfa->transitionCount; i = i + 1) {
      if (nfa->transitions[i] != (clexTransition *)0x0) {
        clexNfaDestroyInternal(nfa->transitions[i]->to,seen);
        free(nfa->transitions[i]);
      }
    }
    if (nfa->compiled != (clexCompiledNfa *)0x0) {
      compiledNfaFree(nfa->compiled);
      free(nfa->compiled);
    }
    free(nfa->transitions);
    free(nfa);
  }
  return;
}