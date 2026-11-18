ptrdiff_t __cdecl argmatch(const char *arg, const char *const *arglist, const void *vallist, size_t valsize)
{
    size_t arglen = strlen(arg);
    ptrdiff_t matchind = -1;
    bool ambiguous = false;

    for (ptrdiff_t i = 0; arglist[i] != NULL; ++i)
    {
        // Check if the current argument starts with the provided string
        if (strncmp(arglist[i], arg, arglen) == 0)
        {
            // If it's an exact match, return the index immediately
            if (strlen(arglist[i]) == arglen)
            {
                return i;
            }
            
            // Otherwise, it's a partial match (abbreviation)
            if (matchind == -1)
            {
                // First partial match found
                matchind = i;
            }
            else if (!vallist || memcmp((const char *)vallist + matchind * valsize, 
                                        (const char *)vallist + i * valsize, 
                                        valsize) != 0)
            {
                // If there's no value list to differentiate them, or if their 
                // associated values differ, the abbreviation is ambiguous.
                ambiguous = true;
            }
        }
    }

    if (ambiguous)
    {
        return -2;
    }
    
    return matchind;
}