cJSON_bool add_item_to_array(cJSON *target_array, cJSON *new_item)
{
    // Validate input pointers and prevent self-referencing
    if (new_item == NULL || target_array == NULL || target_array == new_item) {
        return 0;
    }

    // If the array is empty, initialize it with the new item
    if (target_array->child == NULL) {
        target_array->child = new_item;
        new_item->prev = new_item;
        new_item->next = NULL;
    } else {
        // Append the item to the end of the existing array
        suffix_object(target_array->child->prev, new_item);
        target_array->child->prev = new_item;
    }
    return 1;
}