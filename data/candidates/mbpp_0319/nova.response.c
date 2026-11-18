static struct wordent *func0(char *s, int *np) {
    static struct wordent head, *list, *end;
    char t[MAXLEN];
    char *q;
    int nw = 0;
    int len, i, j;
    int wcnt = 0;

    strcpy(t, s);
    for (i = 0; (len = strlen(t)); i += len, nw++) {
        if (getword(t, i, len, &end, 0) == 0)
            break;
        wcnt++;
        len = end - i;
        if ((q = (char *)malloc((len + 1) * sizeof(char))) == NULL)
            return NULL;
        strncpy(q, t + i, len);
        q[len] = '\0';
        list = &head;
        end = &head;
        while ((end->next!= NULL))
            end = end->next;
        end->next = (struct wordent *)malloc(sizeof(struct wordent));
        end = end->next;
        end->word = q;
    }
    end->next = NULL;
    *np = nw;
    return &head;
}