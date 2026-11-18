int cJSON_GetArraySize(cJSON *array)
{
    cJSON *c = array;
    size_t i = 0;

    if (!c)
    {
        return 0;
    }

    for (c = c->child; c; c = c->next, i++)
    {
    }

    return (int)i;
}