_Bool collectReachableNodes(clexNode *initialNode, NodeVec *reachableNodes)
{
    // Validate input pointers to prevent null dereference
    if (initialNode == NULL || reachableNodes == NULL) {
        return false;
    }

    // Add the starting node to the collection of reachable nodes
    if (!nodeVecPush(reachableNodes, initialNode)) {
        return false;
    }

    // Iterate through all nodes currently in the collection
    for (size_t currentNodeIndex = 0; currentNodeIndex < reachableNodes->size; currentNodeIndex++) {
        clexNode *currentNode = reachableNodes->items[currentNodeIndex];
        // Check each transition from the current node
        for (size_t transitionIndex = 0; transitionIndex < currentNode->transitionCount; transitionIndex++) {
            clexTransition *currentTransition = currentNode->transitions[transitionIndex];
            // Ensure the transition and its target node are valid
            if (currentTransition != NULL && currentTransition->to != NULL) {
                // If the target node hasn't been visited yet, add it to the collection
                if (!nodeVecContains(reachableNodes, currentTransition->to)) {
                    if (!nodeVecPush(reachableNodes, currentTransition->to)) {
                        return false;
                    }
                }
            }
        }
    }

    return true;
}