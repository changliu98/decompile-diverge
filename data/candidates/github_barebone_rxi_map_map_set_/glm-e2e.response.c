int map_set_(struct map *m, void *key, void *value, int vsize) {
    struct map_node **ref = map_getref(m, key);
    
    // If the key already exists, update its value
    if (ref != NULL) {
        // (*ref) points to the map_node. 
        // The value pointer is located at offset 0x8 inside the map_node struct.
        memcpy((*ref)[1], value, (size_t)vsize);
        return 0;
    }

    // Key doesn't exist, create a new node
    struct map_node *node = map_newnode(key, value, vsize);
    if (node == NULL) {
        goto fail;
    }

    // Check if the map needs to be resized (count >= nbuckets)
    if (m->count >= m->nbuckets) {
        unsigned int new_size;
        if (m->nbuckets > 0) {
            new_size = m->nbuckets * 2;
        } else {
            new_size = 1;
        }
        
        int status = map_resize(m, new_size);
        if (status != 0) {
            goto fail;
        }
    }

    // Insert the new node into the map
    map_addnode(m, node);
    m->count++;
    return 0;

fail:
    if (node != NULL) {
        free(node);
    }
    return -1;
}