bool collectReachableNodes(struct Node *node, struct NodeArray *arr) {
    if (node == NULL || arr == NULL) {
        return false;
    }
    
    if (!some_check_1(arr, node)) {
        return false;
    }
    
    for (unsigned long i = 0; i < arr->count; i++) {
        struct Node *current = arr->nodes[i];
        
        for (unsigned long j = 0; j < current->neighbor_count; j++) {
            struct Node *neighbor = current->neighbors[j];
            
            // If neighbor is NULL or its neighbor_count is 0, skip to next iteration
            if (neighbor == NULL || neighbor->neighbor_count == 0) {
                continue;
            }
            
            if (some_check_2(arr, neighbor)) {
                continue;
            }
            
            if (!some_check_3(arr, neighbor)) {
                return false;
            }
        }
    }
    
    return true;
}