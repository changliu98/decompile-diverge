cJSON_bool add_item_to_array(cJSON *array, cJSON *item)
{
    if ((item == NULL) || (array == NULL) || (array == item))
    {
        return ((cJSON_bool)0);
    }

    if (array->child == NULL)
    {
        array->child = item;
        item->prev = item;
        item->next = NULL;
    }
    else if (array->child->prev != NULL)
    {
        suffix_object(array->child->prev, item);
        array->child->prev = item;
    }

    return ((cJSON_bool)1);
}