long argmatch(const char *arg, char *const *strlist, const void *vallist, long size) {
    long arg_len = strlen(arg);
    long match_index = -1;
    char ambiguous = 0;
    long i = 0;

    while (strlist[i] != NULL) {
        if (strncmp(strlist[i], arg, arg_len) == 0) {
            if (strlen(strlist[i]) == arg_len) {
                return i;
            }
            
            if (match_index == -1) {
                match_index = i;
            } else {
                if (vallist != NULL && size > 0) {
                    if (memcmp(vallist + match_index * size, vallist + i * size, size) != 0) {
                        ambiguous = 1;
                    }
                } else {
                    ambiguous = 1;
                }
            }
        }
        i++;
    }

    if (ambiguous) {
        return -2;
    }
    
    return match_index;
}