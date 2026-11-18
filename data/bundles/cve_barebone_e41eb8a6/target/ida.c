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
  int i; // [rsp+Ch] [rbp-44h]
  int ia; // [rsp+Ch] [rbp-44h]
  int contextPrefixL; // [rsp+10h] [rbp-40h]
  int groupNameL; // [rsp+14h] [rbp-3Ch]

  if ( !oidLen || !oidIndex )
    return 1;
  groupNameL = *oidIndex;
  contextPrefixL = oidIndex[groupNameL + 1];
  if ( (_DWORD)oidLen != contextPrefixL + groupNameL + 4 )
    return 1;
  if ( !contextPrefix || !groupName )
    return 1;
  *groupName = (unsigned __int8 *)malloc(groupNameL + 1);
  if ( !*groupName )
    return 1;
  *contextPrefix = (unsigned __int8 *)malloc(contextPrefixL + 1);
  if ( *contextPrefix )
  {
    *contextPrefixLen = contextPrefixL;
    *groupNameLen = groupNameL;
    for ( i = 0; i < groupNameL; ++i )
    {
      if ( oidIndex[i + 1] > 0xFF )
      {
LABEL_16:
        free(*groupName);
        free(*contextPrefix);
        return 1;
      }
      (*groupName)[i] = oidIndex[i + 1];
    }
    (*groupName)[groupNameL] = 0;
    for ( ia = 0; ia < contextPrefixL; ++ia )
    {
      if ( oidIndex[groupNameL + 2 + ia] > 0xFF )
        goto LABEL_16;
      (*contextPrefix)[ia] = oidIndex[groupNameL + 2 + ia];
    }
    (*contextPrefix)[contextPrefixL] = 0;
    *model = oidIndex[contextPrefixL + 2 + groupNameL];
    *level = oidIndex[contextPrefixL + 3 + groupNameL];
    return 0;
  }
  else
  {
    free(*groupName);
    return 1;
  }
}