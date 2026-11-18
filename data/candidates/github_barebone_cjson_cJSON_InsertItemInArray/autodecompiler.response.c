int cJSON_InsertItemInArray(cJSON *array, int which, cJSON *newitem)
{
    cJSON *after_inserted = NULL;
    int ret;

    if ((which < 0) || (newitem == NULL))
    {
        ret = 0;
    }
    else
    {
        after_inserted = get_array_item(array, (size_t)which);
        if (after_inserted == NULL)
        {
            ret = add_item_to_array(array, newitem);
        }
        else
        {
            if (!((after_inserted)->next) && (after_inserted != array->child_end))
            {
                ret = 0;
            }
            else
            {
                newitem->next = after_inserted;
                newitem->prev = after_inserted->prev;
                after_inserted->prev = newitem;
                if (after_inserted == array->child_end)
                {
                    array->child_end = newitem;
                }
                else
                {
                    newitem->prev->next = newitem;
                }
                ret = 1;
            }
        }
    }

    return ret;
}