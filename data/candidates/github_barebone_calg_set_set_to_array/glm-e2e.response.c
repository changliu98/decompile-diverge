void** set_to_array(struct Set *set) {
    void **array = NULL;
    
    // Allocate memory for an array of pointers. 
    // The size is set->size * 8 bytes (shl $0x3 is equivalent to multiplying by 8)
    void **allocated_array = malloc(set->size * 8);
    array = allocated_array;
    
    // If malloc fails, return NULL
    if (array == NULL) {
        return NULL;
    }
    
    int out_idx = 0;
    
    // Iterate over each bucket
    for (size_t i = 0; i < set->capacity; i++) {
        struct SetNode *node = set->buckets[i];
        
        // Iterate over the linked list in the current bucket
        while (node != NULL) {
            // Copy the data pointer into the array
            array[out_idx] = node->data;
            out_idx++;
            
            // Move to the next node
            node = node->next;
        }
    }
    
    return array;
}