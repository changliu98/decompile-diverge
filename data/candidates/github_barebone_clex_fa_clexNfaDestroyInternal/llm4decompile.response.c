void clexNfaDestroyInternal(clexNode *nfa, NodeVec *seen)
{
 if (!nfa || nodeVecContains(seen, nfa))
  return;

 if (!nodeVecPush(seen, nfa))
  return;

 for (size_t i = 0; i < nfa->transitionCount; ++i)
 {
  if (!nfa->transitions[i])
   continue;

  clexNfaDestroyInternal(nfa->transitions[i]->to, seen);
  free(nfa->transitions[i]);
 }

 if (nfa->compiled)
 {
  compiledNfaFree(nfa->compiled);
  free(nfa->compiled);
 }

 free(nfa->transitions);
 free(nfa);
}