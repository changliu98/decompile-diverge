int linenoiseHistorySetMaxLen(int len) {
    if (len < 1) {
        return 0;
    }

    if (history) {
        int old_len = historyMaxLen;
        char **new_history = (char **)malloc(sizeof(char *) * len);
        
        if (!new_history) {
            return 0;
        }

        // If the new max length is less than the current history length,
        // we need to truncate the oldest entries.
        if (len < old_len) {
            int i;
            // Free the entries that fall outside the new max length
            for (i = 0; i < old_len - len; i++) {
                free(history[i]);
            }
            old_len = len;
        }

        // Zero out the new history buffer
        memset(new_history, 0, sizeof(char *) * len);

        // Copy the remaining valid history entries to the new buffer
        // history + (historyMaxLen - old_len) skips the freed entries
        memcpy(new_history, history + (historyMaxLen - old_len), sizeof(char *) * old_len);

        // Free the old history array container (but not the strings themselves)
        free(history);
        
        history = new_history;
    }

    historyMaxLen = len;

    // If the current history length exceeds the new max length, cap it
    if (historyLen > historyMaxLen) {
        historyLen = historyMaxLen;
    }

    return 1;
}