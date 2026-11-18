cJSON *cJSON_CreateString(const char *string) {
    cJSON *item;
    cJSON *ret;

    item = cJSON_New_Item();
    if (item != NULL) {
        // 0x10 corresponds to the cJSON_String type enum
        item->type = 0x10; 
        item->valuestring = cJSON_strdup(string);
        
        if (item->valuestring == NULL) {
            cJSON_Delete(item);
            ret = NULL;
        } else {
            ret = item;
        }
    } else {
        ret = item;
    }
    
    return ret;
}