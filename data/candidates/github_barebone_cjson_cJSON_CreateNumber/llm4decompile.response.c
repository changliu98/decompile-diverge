cJSON * cJSON_CreateNumber(double num)
{
    cJSON *item = cJSON_New_Item(&global_hooks);
    if(item)
    {
        item->type = (8);
        item->valuedouble = num;


        if(num >= (double)0x7fffffff)
        {
            item->valueint = (int)0x7fffffff;
        }
        else if(num <= (double)(int)0x80000000)
        {
            item->valueint = (int)0x80000000;
        }
        else
        {
            item->valueint = (int)num;
        }
    }

    return item;
}