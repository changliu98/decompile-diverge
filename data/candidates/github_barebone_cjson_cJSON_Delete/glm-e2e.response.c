define cJSON_StringIsConst 0x0200

void cJSON_Delete(struct cJSON *item) {
    struct cJSON *next;
    
    while (item != NULL) {
        next = item->next;
        
        if ((item->type & cJSON_IsReference) == 0) {
            if (item->child != NULL) {
                cJSON_Delete(item->child);
            }
            
            if (item->valuestring != NULL) {
                cJSON_free(item->valuestring);
                item->valuestring = NULL;
            }
            
            if (item->string != NULL) {
                cJSON_free(item->string);
                item->string = NULL;
            }
        }
        
        cJSON_free(item);
        item = next;
    }
}