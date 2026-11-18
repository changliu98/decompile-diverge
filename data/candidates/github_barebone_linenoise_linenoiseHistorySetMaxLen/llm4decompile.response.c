int linenoiseHistorySetMaxLen(int len) {
    char **new;
    int tocopy = history_len > len ? len : history_len;

    if (len < 1) return 0;

    if (history) {
        new = malloc(sizeof(char*)*len);
        if (!new) return 0;

        /* On copy only the needed items */
        if (len < history_len) {
            int j;

            for (j = 0; j < history_len-len; j++)
                free(history[j]);
        }
        memset(new,0,(size_t)sizeof(char*)*len);
        memcpy(new,history+history_len-tocopy,
            (size_t)sizeof(char*)*tocopy);
        free(history);
        history = new;
    }

    if (len < history_len) history_len = len;
    history_max_len = len;
    return 1;
}