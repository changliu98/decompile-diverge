bool ensureNodeTransitionCapacity(Node *node, uint64_t required_capacity) {
    if (node == NULL) {
        return false;
    }

    if (node->capacity >= required_capacity) {
        return true;
    }

    uint64_t current_capacity = node->capacity;
    if (current_capacity == 0) {
        current_capacity = 4;
    }

    uint64_t new_capacity = current_capacity;
    while (new_capacity < required_capacity) {
        if (new_capacity > 0x7FFFFFFFFFFFFFFF) {
            new_capacity = required_capacity;
            break;
        }
        new_capacity <<= 1;
    }

    void *new_transitions = realloc(node->transitions, new_capacity * 8);
    if (new_transitions == NULL) {
        return false;
    }

    memset((char *)new_transitions + (node->capacity * 8), 0, (new_capacity - node->capacity) * 8);

    node->transitions = new_transitions;
    node->capacity = new_capacity;

    return true;
}