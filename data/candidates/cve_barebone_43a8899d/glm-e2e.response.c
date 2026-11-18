struct object_item *get_object_item(struct object *object, const char *string, int case_sensitive) {
    struct object_item *current_item = NULL;
    struct object_item *found_item = NULL;

    if (object == NULL || string == NULL) {
        return NULL;
    }

    current_item = object->head;

    if (case_sensitive != 0) {
        while (current_item != NULL && strcmp(string, current_item->string) != 0) {
            current_item = current_item->next;
        }
    } else {
        while (current_item != NULL && case_insensitive_strcmp(string, current_item->string) != 0) {
            current_item = current_item->next;
        }
    }

    found_item = current_item;
    return found_item;
}