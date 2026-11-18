char *cJSON_SetValuestring(cJSON *object, const char *valuestring) {
    char *copy = NULL;

    // Check if object is valid, is of type string, and is not a reference
    if (object == NULL || 
        (object->type & cJSON_String) == 0 || 
        (object->type & cJSON_IsReference) != 0)
    {
        return NULL;
    }

    // Check if either the existing valuestring or the new valuestring is NULL
    if (object->valuestring == NULL || valuestring == NULL) {
        return NULL;
    }

    size_t len_value = strlen(valuestring);
    size_t len_orig = strlen(object->valuestring);

    // If the new string is shorter or equal in length
    if (len_value <= len_orig) {
        // Check for potential memory overlap (similar to memmove's conditions)
        if (valuestring + len_value >= object->valuestring &&
            object->valuestring + len_orig >= valuestring)
        {
            return NULL; // Overlap detected, abort to prevent UB
        }

        // Safe to copy directly into the existing buffer
        strcpy(object->valuestring, valuestring);
        copy = object->valuestring;
    } 
    // If the new string is longer, allocate new memory
    else {
        copy = cJSON_strdup(valuestring, NULL); // NULL represents default hooks
        if (copy == NULL) {
            return NULL; // Allocation failed
        }

        // Free the old string if it exists
        if (object->valuestring != NULL) {
            cJSON_free(object->valuestring);
        }

        // Assign the newly allocated string
        object->valuestring = copy;
    }

    return copy;
}