/*
 * Retrieves a specific item from a cJSON object by its name.
 *
 * @param object        Pointer to the cJSON object to search within.
 * @param name          The name (key) of the item to find.
 * @param case_sensitive Flag indicating whether the search should be case-sensitive.
 *                       If 0, the search is case-insensitive; otherwise, it is case-sensitive.
 * @return              Pointer to the found cJSON item, or NULL if not found or if inputs are invalid.
 */
cJSON * get_object_item(cJSON *json_obj, char *key_name, cJSON_bool is_case_sensitive)
{
    cJSON *current_item;

    /* Return NULL if the object or name pointer is invalid */
    if ((json_obj == (cJSON *)0x0) || (key_name == (char *)0x0)) {
        return (cJSON *)0x0;
    }

    /* Start iteration from the first child of the object */
    current_item = json_obj->child;

    if (is_case_sensitive == 0) {
        /* Case-insensitive search: iterate through children until a match is found */
        while (current_item != (cJSON *)0x0) {
            /* Compare names case-insensitively */
            if (case_insensitive_strcmp((uchar *)key_name, (uchar *)current_item->string) == 0) {
                break;
            }
            current_item = current_item->next;
        }
    } else {
        /* Case-sensitive search: iterate through children until a match is found */
        while (current_item != (cJSON *)0x0) {
            /* Compare names case-sensitively */
            if (strcmp(key_name, current_item->string) == 0) {
                break;
            }
            current_item = current_item->next;
        }
    }

    /* Return the found element or NULL if no match was found */
    return current_item;
}