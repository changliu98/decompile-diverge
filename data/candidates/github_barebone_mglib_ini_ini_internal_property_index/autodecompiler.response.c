int ini_internal_property_index(INIHandler *handler, char *name)
{
    int i, j, k, retval;

    if(!handler) return -1;
    if(!name) return -1;

    for(i = 0; i < handler->numsections; i++)
    {
        if(strcasecmp(handler->sections[i].name, name) == 0)
            return -1;
    }

    if(handler->numsections >= handler->maxsections)
    {
        handler->maxsections += 10;
        handler->sections = realloc__bench(handler->sections,
            sizeof(INISection) * handler->maxsections);
    }

    retval = handler->numsections;
    handler->numsections++;

    memset__bench(&handler->sections[retval], 0, sizeof(INISection));
    handler->sections[retval].name = strdup__bench(name);

    for(i = 0; i < handler->numproperties; i++)
    {
        if(handler->properties[i].section > retval)
            handler->properties[i].section++;
    }

    return retval;
}