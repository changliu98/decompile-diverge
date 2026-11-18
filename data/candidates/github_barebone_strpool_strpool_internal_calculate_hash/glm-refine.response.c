unsigned int __cdecl strpool_internal_calculate_hash(const char *string, int length, int ignore_case)
{
    int hash = 5381;

    if (ignore_case)
    {
        for (int i = 0; i < length; ++i)
        {
            char c = string[i];
            // Convert lowercase ASCII letters to uppercase
            if (c >= 'a' && c <= 'z')
                c -= 32;
            
            hash = (33 * hash) ^ c;
        }
    }
    else
    {
        for (int i = 0; i < length; ++i)
        {
            hash = (33 * hash) ^ string[i];
        }
    }

    // Ensure the hash is never zero
    return hash ? hash : 1;
}