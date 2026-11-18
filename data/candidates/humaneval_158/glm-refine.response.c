char *__cdecl func0(char **words, int count)
{
    char *max_word = "";
    int max_unique_count = 0;

    for (int i = 0; i < count; ++i)
    {
        char unique[256] = {0};
        int unique_count = 0;

        // Count unique characters in the current word
        for (int j = 0; words[i][j]; ++j)
        {
            if (!strchr(unique, words[i][j]))
            {
                int len = strlen(unique);
                unique[len] = words[i][j];
                unique[len + 1] = '\0';
                ++unique_count;
            }
        }

        // Update the max word if this word has more unique characters,
        // or if it ties but is lexicographically smaller.
        if (unique_count > max_unique_count || 
           (unique_count == max_unique_count && strcmp(words[i], max_word) < 0))
        {
            max_word = words[i];
            max_unique_count = unique_count;
        }
    }

    return max_word;
}