void sort_even(float *array, int length, float *dest)
{
    float *tmp = malloc((length / 2 + 1) * sizeof(float));
    int tmp_length = 0;
    int i, j, k;
    float t;

    for (i = 0; ; i += 2)
    {
        if (i >= length)
            break;
        tmp[tmp_length++] = array[i];
    }

    for (i = 0; i < tmp_length - 1; i++)
    {
        for (j = 0; j < tmp_length - i - 1; j++)
        {
            if (tmp[j] > tmp[j + 1])
            {
                t = tmp[j];
                tmp[j] = tmp[j + 1];
                tmp[j + 1] = t;
            }
        }
    }

    for (i = 0; i < length; i++)
    {
        if (i % 2 == 0)
        {
            dest[i] = tmp[i / 2];
        }
        else
        {
            dest[i] = array[i];
        }
    }
    free(tmp);
}