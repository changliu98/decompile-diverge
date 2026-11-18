int access_parse_oid(oid *oidIndex,size_t oidLen,uchar **groupName,size_t *groupNameLen,
                    uchar **contextPrefix,size_t *contextPrefixLen,int *model,int *level)

{
  int iVar1;
  int iVar2;
  uchar *puVar3;
  int i;
  int contextPrefixL;
  int groupNameL;
  size_t *contextPrefixLen_local;
  uchar **contextPrefix_local;
  size_t *groupNameLen_local;
  uchar **groupName_local;
  size_t oidLen_local;
  oid *oidIndex_local;
  int local_c;
  
  if ((oidLen == 0) || (oidIndex == (oid *)0x0)) {
    local_c = 1;
  }
  else {
    iVar1 = (int)*oidIndex;
    iVar2 = (int)oidIndex[iVar1 + 1];
    if ((int)oidLen == iVar1 + iVar2 + 4) {
      if ((contextPrefix == (uchar **)0x0) || (groupName == (uchar **)0x0)) {
        local_c = 1;
      }
      else {
        puVar3 = malloc((long)(iVar1 + 1));
        *groupName = puVar3;
        if (*groupName == (uchar *)0x0) {
          local_c = 1;
        }
        else {
          puVar3 = malloc((long)(iVar2 + 1));
          *contextPrefix = puVar3;
          if (*contextPrefix == (uchar *)0x0) {
            free(*groupName);
            local_c = 1;
          }
          else {
            *contextPrefixLen = (long)iVar2;
            *groupNameLen = (long)iVar1;
            for (i = 0; i < iVar1; i = i + 1) {
              if (0xff < oidIndex[i + 1]) {
                free(*groupName);
                free(*contextPrefix);
                return 1;
              }
              (*groupName)[i] = (uchar)oidIndex[i + 1];
            }
            (*groupName)[iVar1] = '\0';
            for (i = 0; i < iVar2; i = i + 1) {
              if (0xff < oidIndex[i + iVar1 + 2]) {
                free(*groupName);
                free(*contextPrefix);
                return 1;
              }
              (*contextPrefix)[i] = (uchar)oidIndex[i + iVar1 + 2];
            }
            (*contextPrefix)[iVar2] = '\0';
            *model = (int)oidIndex[iVar1 + iVar2 + 2];
            *level = (int)oidIndex[iVar1 + iVar2 + 3];
            local_c = 0;
          }
        }
      }
    }
    else {
      local_c = 1;
    }
  }
  return local_c;
}