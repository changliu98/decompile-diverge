int __cdecl compter_mots(char *saisie, size_t *max_length)
{
    size_t current_length = 0;
    size_t best_length = 0;
    int in_quotes = 0;
    int words = 0;
    char *p;

    // Strip trailing spaces
    for (p = saisie + strlen(saisie) - 1; *p == ' '; --p)
        *p = '\0';

    // Skip leading spaces
    for (p = saisie; *p == ' '; ++p)
        ;

    if (*p)
        words = 1;

    while (*p)
    {
        if (*p == '"' || *p == '\'')
        {
            in_quotes = !in_quotes;
        }
        else if (*p != ' ' || in_quotes)
        {
            // If it's not a space, or if it is a space but we're inside quotes
            ++current_length;
        }
        else
        {
            // Word boundary found
            if (current_length > best_length)
                best_length = current_length;
            
            current_length = 0;
            ++words;

            // Skip consecutive spaces
            while (*p == ' ')
                ++p;
            continue; // Jumps back to evaluate while(*p), avoiding a double-increment
        }
        ++p;
    }

    // Check the length of the final word
    if (current_length > best_length)
        best_length = current_length;

    *max_length = best_length;
    return words;
}