static void clexNfaDestroyInternal(ClexNFA *nfa, NodeVec *visited) {
  if (nfa == NULL) {
    return;
  }
  if (nodeVecContains(visited, nfa)) {
    return;
  }
  if (nodeVecPush(visited, nfa)) {
    for (size_t i = 0; i < nfa->numTransitions; ++i) {
      if (nfa->transitions[i] != NULL) {
        clexNfaDestroyInternal(nfa->transitions[i]->destination, visited);
        free(nfa->transitions[i]);
      }
    }
    if (nfa->compiled != NULL) {
      compiledNfaFree(nfa->compiled);
      free(nfa->compiled);
    }
    free(nfa->transitions);
    free(nfa);
  }
}