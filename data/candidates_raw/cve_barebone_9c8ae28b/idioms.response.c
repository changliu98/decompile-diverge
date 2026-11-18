void messageAddArgument(struct message *m, char *arg)
{
    if (m != ((void *)0))
    {
        if (arg == ((void *)0))
        {
            return;
        }
        for (; (*iswspace())[*arg]; arg++)
        {
        }
        if (*arg == '\0')
        {
            return;
        }
        if (isQuotedString(arg))
        {
            int i;
            for (i = 0; i < m->numberOfArguments && m->mimeArguments[i]; i++)
            {
                if (isArgumentEqual(arg, m->mimeArguments[i]))
                {
                    return;
                }
            }
            if (i == m->numberOfArguments)
            {
                char **newArguments = (char **)messageRealloc(m->mimeArguments,
                                                               (m->numberOfArguments + 1) * sizeof(char *));
                if (newArguments == ((void *)0))
                {
                    m->numberOfArguments--;
                    return;
                }
                m->mimeArguments = newArguments;
            }
            m->mimeArguments[i] = messageCopyString(arg);
            char *arg = m->mimeArguments[i];
            if (arg != ((void *)0))
            {
                if (strchr(arg, '=') == ((void *)0))
                {
                    if (strncasecmp(arg, "charset=", 8) == 0)
                    {
                        if (strncasecmp(arg, "charset=\"", 10) == 0)
                        {
                            arg += 10;
                        }
                        else
                        {
                            arg += 8;
                        }
                        if (strchr(arg, '\"') == ((void *)0))
                        {
                            return;
                        }
                        char *end = strchr(arg, '\"');
                        if (end == ((void *)0))
                        {
                            return;
                        }
                        *end = '\0';
                    }
                }
                if (strncasecmp(arg, "Content-Type", 11) == 0
                    || strncasecmp(arg, "content-type", 11) == 0)
                {
                    if (strncasecmp(arg, "content-type", 11) == 0)
                    {
                        arg += 11;
                    }
                    else
                    {
                        arg += 11;
                    }
                    if (strchr(arg, '=') == ((void *)0))
                    {
                        return;
                    }
                    char *end = strchr(arg, '=');
                    if (end == ((void *)0))
                    {
                        return;
                    }
                    *end = '\0';
                }
                if (messageGetContentType(m) == NOMIME)
                {
                    messageSetContentType(m, "application");
                }
            }
        }
    }
    else
    {
        setError("m != NULL", "/work/harness.c", 346, "void messageAddArgument(message *, const char *)");
    }
}