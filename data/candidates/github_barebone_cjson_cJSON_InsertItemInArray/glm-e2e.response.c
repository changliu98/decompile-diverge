bool cJSON_InsertItemInArray(cJSON *array, int which, cJSON *newitem) {
    cJSON *after_inserted = NULL;

    // Check for invalid arguments
    if (which < 0 || newitem == NULL) {
        return false;
    }

    // Get the item currently at the requested index
    after_inserted = get_array_item(array, which);

    // If the index is out of bounds (beyond the end of the array)
    if (after_inserted == NULL) {
        return cJSON_AddItemToArray(array, newitem);
    }

    // If the item to insert before is the first element, or it doesn't have a previous element
    if (after_inserted == array->child || after_inserted->prev == NULL) {
        return false;
    }

    // Link the new item into the doubly-linked list
    newitem->next = after_inserted;
    newitem->prev = after_inserted->prev;
    after_inserted->prev->next = newitem;
    after_inserted->prev = newitem;

    // If we inserted before the head of the list, update the array's child pointer
    if (after_inserted == array->child) {
        array->child = newitem;
    } else {
        // Otherwise, make sure the previous item's next pointer points to the new item
        newitem->prev->next = newitem;
    }

    return true;
}