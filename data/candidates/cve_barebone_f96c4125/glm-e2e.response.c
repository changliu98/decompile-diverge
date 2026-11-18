void special_keys(char *str) {
    char *unquoted = nb_unquote(str, 0);
    char *token = strtok(unquoted, " ");

    while (token != NULL) {
        char buf[256];
        char keys[100];
        int idx = 0;
        
        char *dash = strchr(token, '-');
        if (dash != NULL) {
            *dash = '\0';
            
            while (*token != '\0') {
                char c = *token;
                if (c == 'A' || c == 'C' || c == 'M' || c == 'S') {
                    keys[idx++] = c;
                    keys[idx++] = '-';
                }
                token++;
            }
        }
        
        if ((size_t)strlen(token) + idx < 64) {
            strcpy(&keys[idx], token);
            vim_snprintf(buf, 256, "<%s>", keys);
            do_map(0, buf, 1, keys);
        }
        
        token = strtok(NULL, " ");
    }
    
    vim_free(unquoted);
}