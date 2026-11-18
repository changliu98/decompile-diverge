cJSON * cJSON_CreateNumber(double num)
{
    cJSON *item = cJSON_New_Item(&global_hooks);
    if(item)
    {
        item->type = (1 << 3);
        item->valuedouble = num;


        if (num >= 2147483647)
        {
            item->valueint = 2147483647;
        }
        else if (num <= (-2147483647 - 1))
        {
            item->valueint = -2147483647 - 1;
        }
        else
        {
            item->valueint = (long)num;
        }
    }

    return item;
}