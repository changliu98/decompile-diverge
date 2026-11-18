int XMLDoc_remove_node(struct XMLDoc *doc, int index, int free_data) {
    void **new_nodes = NULL;
    
    // Check for valid document, magic number, and index bounds
    if (!doc || doc->magic != 0x19770522 || index < 0 || index > doc->node_count) {
        return 0;
    }
    
    // If there's only 1 node, we don't need to allocate a new array
    if (doc->node_count == 1) {
        new_nodes = NULL;
    } else {
        // Allocate new array for the remaining nodes
        new_nodes = malloc((size_t)(doc->node_count - 1) * 8);
        if (!new_nodes) {
            return 0;
        }
    }
    
    // Free the node at the given index
    XMLNode_free(doc->nodes[index]);
    
    // Conditionally free its associated data
    if (free_data) {
        XMLNode_free_data(doc->nodes[index]);
    }
    
    // If we have a new array, copy the remaining nodes into it
    if (new_nodes) {
        // Copy nodes before the removed index
        if (index > 0) {
            memcpy(new_nodes, doc->nodes, (size_t)index * 8);
        }
        
        // Copy nodes after the removed index
        if (doc->node_count - index - 1 > 0) {
            memcpy(
                (char *)new_nodes + (size_t)index * 8,
                (char *)doc->nodes + (size_t)(index + 1) * 8,
                (size_t)(doc->node_count - index - 1) * 8
            );
        }
    }
    
    // Free the old nodes array
    if (doc->nodes) {
        free(doc->nodes);
    }
    
    // Update the document's node array and count
    doc->nodes = new_nodes;
    doc->node_count--;
    
    return 1;
}