char* func0(char* str)
{
    char* ret;
    char current[50];
    int current_index;
    int out_index;
    int i, j, k;
    int len;
    char temp;

    len = strlen(str);
    ret = (char*)malloc((size_t)(len + 2));

    out_index = 0;
    current_index = 0;
    for (i = 0; i <= len; i++)
    {
        if (str[i] == ' ' || str[i] == 0)
        {
            for (j = 0; j < current_index - 1; j++)
            {
                for (k = j + 1; k < current_index; k++)
                {
                    if (current[j] > current[k])
                    {
                        temp = current[j];
                        current[j] = current[k];
                        current[k] = temp;
                    }
                }
            }
            if (out_index > 0)
            {
                ret[out_index] = ' ';
                out_index++;
            }
            for (j = 0; j < current_index; j++)
            {
                ret[out_index] = current[j];
                out_index++;
            }
            current_index = 0;
        }
        else
        {
            current[current_index] = str[i];
            current_index++;
        }
    }
    ret[out_index] = 0;

    return ret;
}