cJSON *cJSON_CreateDoubleArray(double *numbers, int count)
{
    size_t i = 0;
    cJSON *n = 0, *p = 0, *a = 0;

    if ((count < 0) || (numbers == NULL))
    {
        return NULL;
    }

    a = cJSON_CreateArray();

    for (i = 0; a && (i < (size_t)count); i++)
    {
        n = cJSON_CreateNumber(numbers[i]);
        if (!n)
        {
            cJSON_Delete(a);
            return NULL;
        }
        if (!(i ? suffix_object(p, n) : (a->child = n)))
        {
            return NULL;
        }
        p = n;
    }


    if (a && a->child)
    {
        a->child->prev = n;
    }

    return a;
}