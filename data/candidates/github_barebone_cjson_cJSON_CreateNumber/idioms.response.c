struct cJSON *cJSON_CreateNumber(double value)
{
    struct cJSON *item = cJSON_New_Item();
    if (item)
    {
        item->type = cJSON_Number;
        item->valuedouble = value;
        if (value >= 2147483647.0)
            item->valueint = 0x7fffffff;
        else if (value <= (-2147483647 - 1.0))
            item->valueint = (-0x7fffffff - 1);
        else
            item->valueint = (int)value;
    }
    return item;
}