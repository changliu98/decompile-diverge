cJSON *cJSON_AddRawToObject(cJSON *object, const char *name, const char *raw) {
    cJSON *new_item;
    cJSON *ret;

    new_item = cJSON_CreateRaw(raw);
    
    // The 4th argument is a global pointer (likely memory allocation hooks)
    // The 5th argument is 0 (false), likely indicating a non-constant string
    if (add_item_to_object(object, name, new_item, &hooks, false)) {
        ret = new_item;
    } else {
        cJSON_Delete(new_item);
        ret = NULL;
    }
    
    return ret;
}