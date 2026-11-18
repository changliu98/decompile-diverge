void __cdecl clexNfaDestroyInternal(clexNode *nfa, NodeVec *seen) {
    // Guard against null input or cyclic revisitation
    if (nfa == NULL || nodeVecContains(seen, nfa) || !nodeVecPush(seen, nfa)) {
        return;
    }

    // Recursively destroy all child nodes and their transitions
    for (size_t i = 0; i < nfa->transitionCount; ++i) {
        if (nfa->transitions[i] != NULL) {
            clexNfaDestroyInternal(nfa->transitions[i]->to, seen);
            free(nfa->transitions[i]);
        }
    }

    // Free compiled data if it exists
    if (nfa->compiled != NULL) {
        compiledNfaFree(nfa->compiled);
        free(nfa->compiled);
    }

    // Free the current node's transition array and the node itself
    free(nfa->transitions);
    free(nfa);
}