int *func0(int *numbers, int size, int *new_size)
{
    int *out = malloc(sizeof(int) * size);
    int *has1 = calloc(size, sizeof(int));
    int *has2 = calloc(size, sizeof(int));
    int has1_count = 0;
    int has2_count = 0;
    int out_count = 0;
    int i;
    for (i = 0; i < size; i++)
    {
        int num = numbers[i];
        int j;
        int found = 0;
        for (j = 0; j < has2_count; j++)
        {
            if (num == has2[j])
            {
                found = 1;
                break;
            }
        }
        if (found)
            continue;
        found = 0;
        for (j = 0; j < has1_count; j++)
        {
            if (num == has1[j])
            {
                found = 1;
                break;
            }
        }
        if (found)
        {
            has2[has2_count++] = num;
        }
        else
        {
            has1[has1_count++] = num;
        }
    }
    int i;
    for (i = 0; i < size; i++)
    {
        int num = numbers[i];
        int j;
        int found = 0;
        for (j = 0; j < has2_count; j++)
        {
            if (num == has2[j])
            {
                found = 1;
                break;
            }
        }
        if (found)
            continue;
        out[out_count++] = num;
    }
    *new_size = out_count;
    free(has1);
    free(has2);
    return out;
}