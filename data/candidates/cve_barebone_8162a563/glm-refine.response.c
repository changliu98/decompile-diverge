int __cdecl access_parse_oid(
        oid *oidIndex,
        size_t oidLen,
        unsigned __int8 **groupName,
        size_t *groupNameLen,
        unsigned __int8 **contextPrefix,
        size_t *contextPrefixLen,
        int *model,
        int *level)
{
    int groupNameL;
    int contextPrefixL;
    int i;

    // Validate basic inputs and lengths
    if (!oidLen || !oidIndex || !contextPrefix || !groupName)
        return 1;

    groupNameL = oidIndex[0];
    contextPrefixL = oidIndex[groupNameL + 1];

    // Expected OID length: 1 (groupNameL) + groupNameL + 1 (contextPrefixL) + contextPrefixL + 2 (model + level)
    if ((int)oidLen != contextPrefixL + groupNameL + 4)
        return 1;

    // Allocate memory for groupName
    *groupName = (unsigned __int8 *)malloc(groupNameL + 1);
    if (!*groupName)
        return 1;

    // Allocate memory for contextPrefix
    *contextPrefix = (unsigned __int8 *)malloc(contextPrefixL + 1);
    if (!*contextPrefix)
    {
        free(*groupName);
        return 1;
    }

    // Set output lengths
    *groupNameLen = groupNameL;
    *contextPrefixLen = contextPrefixL;

    // Parse groupName
    for (i = 0; i < groupNameL; ++i)
    {
        if (oidIndex[i + 1] > 0xFF)
            goto cleanup_and_fail;
        (*groupName)[i] = oidIndex[i + 1];
    }
    (*groupName)[groupNameL] = 0;

    // Parse contextPrefix
    for (i = 0; i < contextPrefixL; ++i)
    {
        if (oidIndex[groupNameL + 2 + i] > 0xFF)
            goto cleanup_and_fail;
        (*contextPrefix)[i] = oidIndex[groupNameL + 2 + i];
    }
    (*contextPrefix)[contextPrefixL] = 0;

    // Extract model and level
    *model = oidIndex[groupNameL + contextPrefixL + 2];
    *level = oidIndex[groupNameL + contextPrefixL + 3];

    return 0;

cleanup_and_fail:
    free(*groupName);
    free(*contextPrefix);
    return 1;
}