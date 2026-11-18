void clexNfaDestroy(struct NFA *nfa) {
 struct NodeVec seen;
 nodeVecInit(&seen, 0);
 clexNfaDestroyInternal(nfa, &seen);
 nodeVecFree(&seen);
}