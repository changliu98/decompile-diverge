char_u *__cdecl regtilde(char_u *source, int magic)
{
    int prevlen;
    int len;
    char_u *p;
    char_u *tmpsub;
    char_u *newsub;

    newsub = source;
    for (p = source; *p; ++p)
    {
        // Check for '~' when magic is set, or '\~' when magic is not set
        if ((*p == '~' && magic) || (*p == '\\' && p[1] == '~' && !magic))
        {
            if (reg_prev_sub)
            {
                prevlen = strlen((const char *)reg_prev_sub);
                len = p - newsub;
                
                tmpsub = alloc(prevlen + strlen((const char *)newsub));
                if (tmpsub)
                {
                    // Copy the part before the '~' or '\~'
                    memmove(tmpsub, newsub, len);
                    
                    // Copy the previous substitution
                    memmove(tmpsub + len, reg_prev_sub, prevlen);
                    
                    // Skip the backslash if not magic
                    if (!magic)
                        ++p;
                    
                    // Copy the rest of the string
                    strcpy((char *)(tmpsub + len + prevlen), (const char *)(p + 1));
                    
                    // Free the old allocation if it's not the original source
                    if (newsub != source)
                        cleanup(newsub);
                        
                    newsub = tmpsub;
                    p = tmpsub + len + prevlen;
                }
            }
            else
            {
                // If no previous substitution, remove the '~' or '\~'
                if (magic)
                {
                    // Shift the remaining string left by 1 to remove '~'
                    memmove(p, p + 1, strlen((const char *)(p + 1)) + 1);
                }
                else
                {
                    // Shift the remaining string left by 2 to remove '\~'
                    memmove(p, p + 2, strlen((const char *)(p + 2)) + 1);
                }
            }
            --p; // Step back to re-evaluate the current position
        }
        else
        {
            // Skip the next character if it's an escape sequence (e.g., '\n')
            if (*p == '\\' && p[1])
                ++p;
            
            // Handle multi-byte characters
            if (has_mbyte)
                p += mb_ptr2len(p) - 1;
        }
    }
    
    // Update the previous substitution with the new result
    cleanup(reg_prev_sub);
    reg_prev_sub = vim_strsave(newsub);
    
    return newsub;
}