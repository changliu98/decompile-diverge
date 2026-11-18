void clexNfaDestroyInternal(NfaNode *node, void *arg) {
    // Check if node is NULL or if it matches specific compiled/finished criteria
    if (node != NULL) {
        if (!clexNfaIsCompiled(node, arg)) {
            if (!clexNfaIsFinished(node, arg)) {
                return;
            }
        }
    } else {
        return;
    }

    // Iterate over all children and recursively destroy them
    for (unsigned long i = 0; i < node->child_count; i++) {
        NfaNode *child = node->children[i];
        if (child != NULL) {
            // Recursively call destroy on the child
            clexNfaDestroyInternal(child, arg);
            
            // Free the child node itself
            free(child);
        }
    }

    // If the node has extra dynamically allocated data, free it
    if (node->extra_data != NULL) {
        nodeVecFree(node->extra_data);
        free(node->extra_data);
    }

    // Free the array of children pointers
    free(node->children);

    // Finally, free the node itself
    free(node);
}