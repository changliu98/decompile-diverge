char **__cdecl func0(const char *paren_string, int *group_count)
{
    int length = strlen(paren_string);
    int level = 0;
    int capacity = 10;
    
    // Allocate initial array of strings (10 pointers = 80 bytes on 64-bit)
    char **groups = (char **)malloc(capacity * sizeof(char *));
    char *buffer = (char *)malloc(length + 1);
    int buffer_index = 0;
    
    *group_count = 0;
    
    for (int i = 0; i < length; ++i)
    {
        char chr = paren_string[i];
        
        if (chr == '(')
        {
            ++level;
            buffer[buffer_index++] = chr;
        }
        else if (chr == ')')
        {
            --level;
            buffer[buffer_index++] = chr;
            
            // If level reaches 0, a complete group has been found
            if (level == 0)
            {
                buffer[buffer_index] = '\0';
                groups[(*group_count)++] = strdup(buffer);
                
                // Double the capacity if we run out of space
                if (*group_count >= capacity)
                {
                    capacity *= 2;
                    groups = (char **)realloc(groups, capacity * sizeof(char *));
                }
                buffer_index = 0;
            }
        }
    }
    
    free(buffer);
    return groups;
}