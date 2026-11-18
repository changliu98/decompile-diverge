bool __cdecl wc_unescape(char *output, const char *wildcard)
{
    while (*wildcard)
    {
        if (*wildcard == '\\')
        {
            // Move past the backslash
            wildcard++;
            if (*wildcard)
            {
                // Copy the escaped character if output buffer is valid
                if (output)
                    *output++ = *wildcard;
                wildcard++;
            }
        }
        else
        {
            // Reject unescaped wildcard characters
            if (*wildcard == '*' || *wildcard == '?' || *wildcard == '[' || *wildcard == ']')
                return false;

            // Copy the regular character if output buffer is valid
            if (output)
                *output++ = *wildcard;
            wildcard++;
        }
    }

    // Null-terminate the output string if the buffer is valid
    if (output)
        *output = '\0';
        
    return true;
}