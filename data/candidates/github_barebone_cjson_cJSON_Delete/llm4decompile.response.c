void cJSON_Delete(cJSON *item)
{
    cJSON *next;

    while (item) {
        next = item->next;
        if (!(item->type & 256) && item->child) {
            cJSON_Delete(item->child);
        }
        if (!(item->type & 256) && item->valuestring) {
            global_hooks.deallocate(item->valuestring);
            item->valuestring = NULL;
        }
        if (!(item->type & 512) && item->string) {
            global_hooks.deallocate(item->string);
            item->string = NULL;
        }
        global_hooks.deallocate(item);
        item = next;
    }
}