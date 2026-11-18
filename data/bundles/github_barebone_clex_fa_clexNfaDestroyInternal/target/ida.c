void __cdecl clexNfaDestroyInternal(clexNode *nfa, NodeVec *seen)
{
  size_t i; // [rsp+8h] [rbp-18h]

  if ( nfa && !nodeVecContains(seen, nfa) && nodeVecPush(seen, nfa) )
  {
    for ( i = 0LL; i < nfa->transitionCount; ++i )
    {
      if ( nfa->transitions[i] )
      {
        clexNfaDestroyInternal(nfa->transitions[i]->to, seen);
        free(nfa->transitions[i]);
      }
    }
    if ( nfa->compiled )
    {
      compiledNfaFree(nfa->compiled);
      free(nfa->compiled);
    }
    free(nfa->transitions);
    free(nfa);
  }
}