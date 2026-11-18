int XMLNode_remove_attribute(struct XMLNode *node, int index) {
    int ret_val;

    // Check for null node, invalid magic number, or out-of-bounds index
    if (node == NULL || node->magic != 0x19770522 || index < 0 || index >= node->attribute_count) {
        ret_val = -1;
        return ret_val;
    }

    struct XMLAttribute *new_attrs = NULL;

    // If there's only 1 attribute, removing it means the new array is just NULL
    if (node->attribute_count != 1) {
        // Allocate a new array smaller by 1 attribute (size = (count - 1) * 24)
        new_attrs = (struct XMLAttribute *)malloc((size_t)(node->attribute_count - 1) * 24);
        if (new_attrs == NULL) {
            ret_val = -1;
            return ret_val;
        }
    }

    struct XMLAttribute *attrs = (struct XMLAttribute *)node->attributes;
    
    // Free the name string of the attribute being removed
    if (attrs[index].name != NULL) {
        free(attrs[index].name);
    }
    
    // Free the value string of the attribute being removed
    if (attrs[index].value != NULL) {
        free(attrs[index].value);
    }

    // If we allocated a new array, copy the remaining attributes over
    if (new_attrs != NULL) {
        // Copy elements before the removed index
        if (index > 0) {
            memcpy(new_attrs, attrs, (size_t)index * 24);
        }
        
        // Copy elements after the removed index
        if (node->attribute_count - index - 1 > 0) {
            memcpy(
                (char *)new_attrs + (size_t)index * 24,
                (char *)attrs + (size_t)(index + 1) * 24,
                (size_t)(node->attribute_count - index - 1) * 24
            );
        }
    }

    // Free the old attributes array
    if (node->attributes != NULL) {
        free(node->attributes);
    }

    // Assign the new array (or NULL) and decrement the count
    node->attributes = new_attrs;
    node->attribute_count--;

    ret_val = node->attribute_count;
    return ret_val;
}