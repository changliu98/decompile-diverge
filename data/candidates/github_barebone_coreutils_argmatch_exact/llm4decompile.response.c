int argmatch_exact(const char *arg, const char **arglist)
{
    int i;

    for (i = 0; arglist[i] != NULL; i++)
        if (!strcmp(arglist[i], arg))
            return i;

    return -1;
}