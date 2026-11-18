void cJSON_Delete(struct cJSON *item)
{
    struct cJSON *next;
    while (item)
    {
        next = item->next;
        if (item->type & (cJSON_String|cJSON_Array))
        {
            if (item->child)
                cJSON_Delete(item->child);
        }
        if (item->type & (cJSON_String|cJSON_Array))
        {
            if (item->valuestring)
            {
                global_hooks.deallocate(item->valuestring);
                item->valuestring = ((void *)0);
            }
        }
        if (item->type & ~(cJSON_String|cJSON_Array))
        {
            if (item->string)
            {
                global_hooks.deallocate(item->string);
                item->string = ((void *)0);
            }
        }
        global_hooks.deallocate(item);
        item = next;
    }
}