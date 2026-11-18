void messageAddArgument(message *m, const char *arg)
{
    int i;
    char **newargs;

    ((m != NULL) ? (void)0 : __assert_fail("m != NULL", "/work/harness.c", 346, "void messageAddArgument(message *, const char *)"));

    if (arg == NULL)
        return;

    while (isspace(*arg))
        arg++;

    if (*arg == '\0')
        return;

    if (!usefulArg(arg))
        return;

    for (i = 0; i < m->numberOfArguments && m->mimeArguments[i] != NULL;
            i++) {
        if (!strcasecmp(arg, m->mimeArguments[i]))
            return;
    }

    if (i == m->numberOfArguments) {
        m->numberOfArguments++;
        newargs = cli_realloc(m->mimeArguments,
                (size_t)(sizeof(char *) * m->numberOfArguments));
        if (newargs == NULL) {
            m->numberOfArguments--;
            return;
        }
        m->mimeArguments = newargs;
    }

    m->mimeArguments[i] = rfc2231(arg);
    if (m->mimeArguments[i] == NULL)
        return;






    if (strchr(m->mimeArguments[i], '=') == NULL
            && strncmp(m->mimeArguments[i], "filename", 8) == 0)
        m->mimeArguments[i][8] = '=';






    if (strncasecmp(m->mimeArguments[i], "filename=", 9) == 0
            || strncasecmp(m->mimeArguments[i], "name=", 5) == 0) {
        if (messageGetMimeType(m) == NOMIME)
            messageSetMimeType(m, "application");
    } else {
        free(m->mimeArguments[i]);
        m->mimeArguments[i] = NULL;
    }
}