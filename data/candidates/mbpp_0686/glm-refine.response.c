char *__cdecl func0(int *test_tup, int size)
{
    char buffer[50];
    dict freq[100];
    int count = 0;

    // Count the frequency of each element in the input array
    for (int i = 0; i < size; ++i)
    {
        int found = 0;
        for (int j = 0; j < count; ++j)
        {
            if (freq[j].key == test_tup[i])
            {
                ++freq[j].value;
                found = 1;
                break;
            }
        }
        if (!found)
        {
            freq[count].key = test_tup[i];
            freq[count].value = 1;
            ++count;
        }
    }

    // Allocate a 1000-byte buffer for the resulting string
    char *result = (char *)malloc(0x3E8u);
    *result = 0; // Initialize as empty string
    
    strcat(result, "{");
    
    // Format the frequency dictionary into the string
    for (int i = 0; i < count; ++i)
    {
        sprintf(buffer, "%d: %d", (unsigned int)freq[i].key, (unsigned int)freq[i].value);
        strcat(result, buffer);
        
        if (i < count - 1)
            strcat(result, ", ");
    }
    
    strcat(result, "}");
    
    return result;
}