void __cdecl special_keys(char_u *args)
{
    char cmdbuf[256];
    char keybuf[64];
    char *save_str;
    char *tok;
    char *sep;
    int i;

    // Unquote and duplicate the arguments string
    save_str = (char *)nb_unquote(args, NULL);

    // Tokenize the string by spaces
    for (tok = strtok(save_str, " "); tok; tok = strtok(NULL, " "))
    {
        i = 0;
        sep = strchr(tok, '-'); // Look for modifier separator (e.g., "C-A")

        if (sep)
        {
            *sep = '\0'; // Split the token at the dash
            
            // Process the modifier characters before the dash
            while (*tok)
            {
                if (IS_MODIFIER(*tok))
                {
                    keybuf[i++] = *tok;
                    keybuf[i++] = '-';
                }
                tok++;
            }
            tok++; // Skip the null terminator we inserted to point to the actual key
        }

        // Ensure the constructed key sequence fits in keybuf (64 bytes)
        if (i + strlen(tok) < 0x40)
        {
            strcpy(&keybuf[i], tok);
            
            // Format the mapping command: <silent><{key}> :nbkey {key}<CR>
            vim_snprintf(cmdbuf, 0x100u, "<silent><%s> :nbkey %s<CR>", keybuf, keybuf);
            
            // Execute the mapping (0, 1, 0 correspond to typical Vim map flags)
            do_map(0, (char_u *)cmdbuf, 1, 0);
        }
    }
    
    vim_free(save_str);
}