cJSON * cJSON_AddNumberToObject(cJSON *object, char *name, double number)
{
    // Create a new cJSON number node with the specified value
    cJSON *number_node = cJSON_CreateNumber(number);
    // Attempt to add the new number node to the parent object
    if (!add_item_to_object(object, name, number_node, &global_hooks, 0)) {
        // If adding fails, delete the created node to prevent memory leaks
        cJSON_Delete(number_node);
        number_node = NULL;
    }
    // Return the created node (or NULL if addition failed)
    return number_node;
}