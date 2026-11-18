char* func0(int* test_tup, int size)
{
    int i;
    int j;
    int count = 0;
    dict freq[100];
    for (i = 0; i < size; i++)
    {
        int found = 0;
        for (j = 0; j < count; j++)
        {
            if (freq[j].key == test_tup[i])
            {
                freq[j].value++;
                found = 1;
                break;
            }
        }
        if (found == 0)
        {
            freq[count].key = test_tup[i];
            freq[count].value = 1;
            count++;
        }
    }
    char* result = malloc(1000);
    result[0] = '\0';
    strcat(result, "{");
    for (i = 0; i < count; i++)
    {
        char buffer[50];
        sprintf(buffer, "%d: %d", freq[i].key, freq[i].value);
        strcat(result, buffer);
        if (i < count - 1)
        {
            strcat(result, ", ");
        }
    }
    strcat(result, "}");
    return result;
}