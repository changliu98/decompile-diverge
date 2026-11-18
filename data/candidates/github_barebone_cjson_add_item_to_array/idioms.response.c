int add_item_to_array(struct cJSON *before, struct cJSON *item)
{
    struct cJSON *current;
    if (!item || !before || (before == item))
        return 0;
    current = before->child;
    if (!current)
    {
        before->child = item;
        item->prev = item;
        item->next = ((void *)0);
    }
    else if (current->prev)
    {
        cJSON_DeleteItem(current->prev, item);
        current->prev = item;
    }
    return 1;
}