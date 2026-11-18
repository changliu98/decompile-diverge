struct cJSON *cJSON_CreateDoubleArray(double *numbers, int count)
{
    struct cJSON *item = ((void *)0); struct cJSON *next = ((void *)0); struct cJSON *last = ((void *)0);
    unsigned long i;
    if (count < 0 || !numbers)
        return ((void *)0);
    item = cJSON_CreateArray();
    for (i = 0; (item && i < count); i++)
    {
        next = cJSON_CreateNumber(numbers[i]);
        if (!next)
        {
            cJSON_Delete(item);
            return ((void *)0);
        }
        if (i == 0)
            item->child = next;
        else
            suffix_object(last, next);
        last = next;
    }
    if (item && item->child)
        item->child->prev = last;
    return item;
}