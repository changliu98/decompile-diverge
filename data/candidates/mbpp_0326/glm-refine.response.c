const char *__cdecl func0(int n, const char **test_list)
{
    char word[50];
    int pos = 0;
    int unique = 0;

    // Iterate over all strings in the test_list
    for (int i = 0; i < n; ++i)
    {
        const char *str = test_list[i];
        
        // Tokenize the string based on whitespace
        while (*str)
        {
            // Check if the character is a space (matches the `_ISspace` flag in __ctype_b_loc)
            if (isspace((unsigned char)*str))
            {
                if (pos > 0)
                {
                    word[pos] = '\0';
                    int found = 0;
                    
                    // Check if the word is already in our list
                    for (int j = 0; j < unique; ++j)
                    {
                        if (strcmp(func0_words[j].word, word) == 0)
                        {
                            func0_words[j].count++;
                            found = 1;
                            break;
                        }
                    }
                    
                    // If not found, add it to the list
                    if (!found)
                    {
                        strcpy(func0_words[unique].word, word);
                        func0_words[unique].count = 1;
                        unique++;
                    }
                    pos = 0;
                }
            }
            else
            {
                word[pos++] = *str;
            }
            ++str;
        }
        
        // Handle the last word in the string if it doesn't end with a space
        if (pos > 0)
        {
            word[pos] = '\0';
            int found = 0;
            
            for (int j = 0; j < unique; ++j)
            {
                if (strcmp(func0_words[j].word, word) == 0)
                {
                    func0_words[j].count++;
                    found = 1;
                    break;
                }
            }
            
            if (!found)
            {
                strcpy(func0_words[unique].word, word);
                func0_words[unique].count = 1;
                unique++;
            }
            pos = 0;
        }
    }

    // Find the word with the maximum count
    int max = 0;
    int index = 0;
    for (int i = 0; i < unique; ++i)
    {
        if (func0_words[i].count > max)
        {
            max = func0_words[i].count;
            index = i;
        }
    }

    return func0_words[index].word;
}