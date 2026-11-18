cJSON_bool cJSON_InsertItemInArray(cJSON *json_array, int index, cJSON *new_node)
{
    // Validate input: 'which' must be non-negative and 'newitem' must not be NULL
    if ((index < 0) || (new_node == NULL)) {
        return 0;
    }

    // Retrieve the existing item at the specified index
    cJSON *existing_node = get_array_item(json_array, (long)index);
    
    // If the index is out of bounds (item not found), append the new item to the end
    if (existing_node == NULL) {
        return add_item_to_array(json_array, new_node);
    }
    // If the target item is the head of the list or has a previous sibling, insert before it
    else if ((existing_node == json_array->child) || (existing_node->prev != NULL)) {
        // Link the new item to the target item and its predecessor
        new_node->next = existing_node;
        new_node->prev = existing_node->prev;
        existing_node->prev = new_node;
        
        // If inserting at the head, update the array's child pointer
        if (existing_node == json_array->child) {
            json_array->child = new_node;
        }
        // Otherwise, link the predecessor to the new item
        else {
            new_node->prev->next = new_node;
        }
        return 1;
    }
    // If the target item is not the head and has no predecessor, insertion is not supported in this manner
    else {
        return 0;
    }
}