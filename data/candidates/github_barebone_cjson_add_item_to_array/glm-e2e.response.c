bool add_item_to_array(cJSON *array, cJSON *item) {
    cJSON *after = NULL;

    if (item == NULL || array == NULL || array == item) {
        return false;
    }

    after = array->child;
    
    if (after == NULL) {
        // Array is empty, make item the only element
        array->child = item;
        item->prev = item;
        item->next = NULL;
    } else {
        // Array has elements, append to the end
        if (after->next != NULL) {
            add_item_to_array(after->next, item);
        }
        after->next = item;
        item->prev = array->child;
    }
    
    return true;
}