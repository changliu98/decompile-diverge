int cJSON_InsertItemBefore(struct cJSON *before, int which, struct cJSON *item)
{
    struct cJSON *after = cJSON_GetItemFromIndex(before, which);
    if(which < 0 || !item)
        return 0;
    if(after)
    {
        if(after == before->child && after->prev)
        {
            item->next = after;
            item->prev = after->prev;
            after->prev = item;
            item->prev->next = item;
        }
        else
            return 0;
    }
    else
    {
        return cJSON_AddItemBefore(before, item);
    }
    return 1;
}