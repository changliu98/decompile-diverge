int *__cdecl func0(const char *music_string, int *count)
{
    int *out = NULL;
    int size = 0;
    int capacity = 0;
    char current[3] = {0};
    
    // Calculate length and create a mutable copy with a trailing space
    int music_string_length = strlen(music_string) + 1;
    char *temp_music_string = (char *)malloc(music_string_length + 1);
    strcpy(temp_music_string, music_string);
    strcat(temp_music_string, " ");

    for (int i = 0; i < music_string_length; ++i)
    {
        if (temp_music_string[i] == ' ')
        {
            if (strcmp(current, "o") == 0)
            {
                APPEND(4);
            }
            else if (strcmp(current, "o|") == 0)
            {
                APPEND(2);
            }
            else if (strcmp(current, ".|") == 0)
            {
                APPEND(1);
            }
            
            // Reset the current token
            current[0] = '\0';
        }
        else
        {
            size_t len = strlen(current);
            // Only append if the token isn't already max length (2 chars + null terminator)
            if (len < 2)
            {
                current[len] = temp_music_string[i];
                current[len + 1] = '\0';
            }
        }
    }

    free(temp_music_string);
    *count = size;
    return out;
}