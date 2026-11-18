char *last_component(char *name)
{
    char *base = name;
    int last_was_slash = 0;

    while (*base == '/')
        base++;

    while (*name) {
        if (*name == '/')
            last_was_slash = 1;
        else if (last_was_slash) {
            last_was_slash = 0;
            base = name;
        }
        name++;
    }
    return base;
}