/*
 * Adds a raw JSON string item to an object.
 *
 * @param object The target cJSON object to add the item to.
 * @param name   The name/key for the new item.
 * @param raw    The raw JSON string content to be added.
 * @return       A pointer to the newly created cJSON item, or NULL on failure.
 */
cJSON * cJSON_AddRawToObject(cJSON *target_object, char *key_name, char *raw_json_string)
{
    /* Create a new raw JSON item with the provided raw string */
    cJSON *new_item = cJSON_CreateRaw(raw_json_string);
    
    /* Attempt to add the item to the object */
    if (!add_item_to_object(target_object, key_name, new_item, &global_hooks, 0)) {
        /* If adding fails, clean up the created item and set pointer to NULL */
        cJSON_Delete(new_item);
        new_item = NULL;
    }
    
    /* Return the item (either successfully added or NULL if failed) */
    return new_item;
}