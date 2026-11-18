int __cdecl access_parse_oid(
        oid *oidIndex,
        size_t oidLen,
        uint8_t **groupName,
        size_t *groupNameLen,
        uint8_t **contextPrefix,
        size_t *contextPrefixLen,
        int *model,
        int *level)
{
  int groupNameL;
  int contextPrefixL;
  int i;

  // Validate basic arguments and length
  if (!oidLen || !oidIndex)
    return 1;

  groupNameL = oidIndex[0];
  contextPrefixL = oidIndex[groupNameL + 1];

  // Expected OID length: groupNameLen + contextPrefixLen + 4 
  // (1 for groupNameLen, 1 for contextPrefixLen, 1 for model, 1 for level)
  if ((int)oidLen != contextPrefixL + groupNameL + 4)
    return 1;

  if (!contextPrefix || !groupName)
    return 1;

  // Allocate memory for groupName
  *groupName = (uint8_t *)malloc(groupNameL + 1);
  if (!*groupName)
    return 1;

  // Allocate memory for contextPrefix
  *contextPrefix = (uint8_t *)malloc(contextPrefixL + 1);
  if (!*contextPrefix)
  {
    free(*groupName);
    return 1;
  }

  // Set output lengths
  *contextPrefixLen = contextPrefixL;
  *groupNameLen = groupNameL;

  // Parse groupName
  for (i = 0; i < groupNameL; ++i)
  {
    if (oidIndex[i + 1] > 0xFF)
      goto cleanup_and_fail;
    (*groupName)[i] = (uint8_t)oidIndex[i + 1];
  }
  (*groupName)[groupNameL] = 0; // Null-terminate

  // Parse contextPrefix
  for (i = 0; i < contextPrefixL; ++i)
  {
    if (oidIndex[groupNameL + 2 + i] > 0xFF)
      goto cleanup_and_fail;
    (*contextPrefix)[i] = (uint8_t)oidIndex[groupNameL + 2 + i];
  }
  (*contextPrefix)[contextPrefixL] = 0; // Null-terminate

  // Extract model and level
  *model = oidIndex[groupNameL + contextPrefixL + 2];
  *level = oidIndex[groupNameL + contextPrefixL + 3];

  return 0; // Success

cleanup_and_fail:
  free(*groupName);
  free(*contextPrefix);
  return 1; // Failure
}