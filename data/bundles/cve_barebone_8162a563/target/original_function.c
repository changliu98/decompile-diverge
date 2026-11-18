__attribute__((noinline))
int
access_parse_oid(oid * oidIndex, size_t oidLen,
                 unsigned char **groupName, size_t * groupNameLen,
                 unsigned char **contextPrefix, size_t * contextPrefixLen,
                 int *model, int *level)
{
    int             groupNameL, contextPrefixL;
    int             i;

    /*
     * first check the validity of the oid 
     */
    if ((oidLen <= 0) || (!oidIndex)) {
        return 1;
    }
    groupNameL = oidIndex[0];
    contextPrefixL = oidIndex[groupNameL + 1];  /* the initial name length */
    if ((int) oidLen != groupNameL + contextPrefixL + 4) {
        return 1;
    }

    /*
     * its valid, malloc the space and store the results 
     */
    if (contextPrefix == NULL || groupName == NULL) {
        return 1;
    }

    *groupName = (unsigned char *) malloc(groupNameL + 1);
    if (*groupName == NULL) {
        return 1;
    }

    *contextPrefix = (unsigned char *) malloc(contextPrefixL + 1);
    if (*contextPrefix == NULL) {
        free(*groupName);
        return 1;
    }

    *contextPrefixLen = contextPrefixL;
    *groupNameLen = groupNameL;

    for (i = 0; i < groupNameL; i++) {
        if (oidIndex[i + 1] > 255) {
            free(*groupName);
            free(*contextPrefix);
            return 1;
        }
        groupName[0][i] = (unsigned char) oidIndex[i + 1];
    }
    groupName[0][groupNameL] = 0;


    for (i = 0; i < contextPrefixL; i++) {
        if (oidIndex[i + groupNameL + 2] > 255) {
            free(*groupName);
            free(*contextPrefix);
            return 1;
        }
        contextPrefix[0][i] = (unsigned char) oidIndex[i + groupNameL + 2];
    }
    contextPrefix[0][contextPrefixL] = 0;

    *model = oidIndex[groupNameL + contextPrefixL + 2];
    *level = oidIndex[groupNameL + contextPrefixL + 3];

    return 0;

}