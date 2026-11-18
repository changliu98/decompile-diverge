bool __cdecl ensureNodeTransitionCapacity(clexNode *node, size_t required)
{
    size_t currentCapacity;
    size_t newCapacity;
    clexTransition **resized;

    if (!node)
        return false;

    if (node->transitionCapacity >= required)
        return true;

    // Initialize the starting capacity to double from, defaulting to 4 if it's currently 0
    currentCapacity = node->transitionCapacity ? node->transitionCapacity : 4;

    // Geometrically grow the capacity until it satisfies the required amount
    for (newCapacity = currentCapacity; newCapacity < required; newCapacity *= 2)
    {
        // Overflow check: If we exceed SIZE_MAX / 2, fall back to the exact required size
        if (newCapacity > 0x7FFFFFFFFFFFFFFFLL)
        {
            newCapacity = required;
            break;
        }
    }

    // Reallocate the transitions array to the new capacity
    resized = (clexTransition **)realloc(node->transitions, newCapacity * sizeof(clexTransition *));
    if (!resized)
        return false;

    // Zero out the newly allocated memory slots
    memset(&resized[node->transitionCapacity], 0, (newCapacity - node->transitionCapacity) * sizeof(clexTransition *));

    node->transitions = resized;
    node->transitionCapacity = newCapacity;

    return true;
}