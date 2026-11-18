char *regtilde(char *dest, int magic) {
    char *p = dest;
    char *new_dest = dest;
    char *np;

    while (*p != '\0') {
        if ((*p == '~' && !magic) || (*p == '\\' && *(p + 1) == '~' && !magic)) {
            if (reg_prev_sub != NULL) {
                int prev_sub_len = strlen(reg_prev_sub);
                int prefix_len = p - new_dest;
                
                np = (char *)alloc(strlen(new_dest) + prev_sub_len);
                if (np != NULL) {
                    memmove(np, new_dest, prefix_len);
                    memmove(np + prefix_len, reg_prev_sub, prev_sub_len);
                    
                    if (!magic) {
                        p++;
                    }
                    
                    strcpy(np + prefix_len + prev_sub_len, p + 1);
                    
                    if (new_dest != dest) {
                        vim_free(new_dest);
                    }
                    
                    new_dest = np;
                    p = new_dest + prefix_len + prev_sub_len;
                }
            } else {
                if (magic) {
                    memmove(p, p + 1, strlen(p + 1) + 1);
                } else {
                    memmove(p, p + 2, strlen(p + 2) + 1);
                }
                p--;
            }
        } else {
            if (*p == '\\' && *(p + 1) != '\0') {
                p++;
            }
            
            if (has_mbyte) {
                p += mb_ptr2len(p) - 1;
            }
        }
        p++;
    }

    vim_free(reg_prev_sub);
    reg_prev_sub = vim_strsave(new_dest);
    
    return new_dest;
}