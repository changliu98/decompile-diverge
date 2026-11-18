void clex_free_nfa(struct clexNode *nfa, struct NodeVec *seen)
{
  if (nfa == ((void *)0))
    return;
  if (clex_node_in_vec(seen, nfa))
    return;
  if (!clex_node_is_start(seen, nfa))
    return;
  for (unsigned long i = 0; i < nfa->transitionCount; i++)
  {
    if (nfa->transitions[i] != ((void *)0))
    {
      clex_free_nfa(nfa->transitions[i]->to, seen);
      clex_free_trans(nfa->transitions[i]);
    }
  }
  if (nfa->compiled != ((void *)0))
  {
    clex_free_trans(nfa->compiled);
    clex_free_trans(nfa->compiled);
  }
  clex_free_trans(nfa->transitions);
  clex_free_trans(nfa);
}