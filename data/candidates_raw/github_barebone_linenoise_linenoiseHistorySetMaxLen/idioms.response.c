int history_set_max_len(int maxlen)
{
    if (maxlen < 1)
        return 0;
    if (history != ((void *)0)) {
        int tocopy = history_len;
        char **newhist = xmalloc(sizeof(char *) * maxlen);
        if (newhist == ((void *)0))
            return 0;
        if (maxlen < tocopy) {
            int i;
            for (i = 0; i < tocopy - maxlen; i++)
                history_free(history[i]);
            tocopy = maxlen;
        }
        array_copy(newhist, 0, newhist + maxlen);
        array_copy(newhist + tocopy, history + (history_len - tocopy),
                   tocopy);
        history_free(history);
        history = newhist;
    }
    history_max_len = maxlen;
    if (history_len > maxlen)
        history_len = history_max_len;
    return 1;
}