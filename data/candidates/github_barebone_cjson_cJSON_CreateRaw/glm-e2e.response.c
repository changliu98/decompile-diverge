struct cJSON *cJSON_CreateRaw(const char *str) {
    struct cJSON *item;
    struct cJSON *result;

    item = cJSON_New_Item();
    if (item != NULL) {
        item->type = 0x80; // Assuming 0x80 corresponds to cJSON_Raw type
        item->valuestring = cJSON_strdup(str);
        
        if (item->valuestring == NULL) {
            cJSON_Delete(item);
            result = NULL;
        } else {
            result = item;
        }
    } else {
        result = item; // item is NULL here
    }
    
    return result;
}