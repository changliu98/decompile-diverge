int
access_parse_oid(oid *oidIndex, size_t oidLen,
   u_char **groupName, size_t *groupNameLen,
   u_char **contextPrefix, size_t *contextPrefixLen,
   int *model, int *level)
{
 int groupNameL, contextPrefixL;
 int i;

 if (oidLen == 0 || oidIndex == NULL)
  return 1;

 groupNameL = *oidIndex;
 contextPrefixL = *(oidIndex + groupNameL + 1);

 if (oidLen != (size_t)(groupNameL + contextPrefixL + 4))
  return 1;

 if (groupName == NULL || contextPrefix == NULL)
  return 1;

 *groupName = malloc((size_t)(groupNameL + 1));
 if (*groupName == NULL)
  return 1;

 *contextPrefix = malloc((size_t)(contextPrefixL + 1));
 if (*contextPrefix == NULL) {
  free(*groupName);
  return 1;
 }

 *contextPrefixLen = (size_t)contextPrefixL;
 *groupNameLen = (size_t)groupNameL;

 for (i = 0; i < groupNameL; i++) {
  if (*(oidIndex + i + 1) > 255) {
   free(*groupName);
   free(*contextPrefix);
   return 1;
  }
  *(*groupName + i) = (u_char)*(oidIndex + i + 1);
 }
 *(*groupName + groupNameL) = '\0';

 for (i = 0; i < contextPrefixL; i++) {
  if (*(oidIndex + i + groupNameL + 2) > 255) {
   free(*groupName);
   free(*contextPrefix);
   return 1;
  }
  *(*contextPrefix + i) = (u_char)*(oidIndex + i + groupNameL + 2);
 }
 *(*contextPrefix + contextPrefixL) = '\0';

 *model = (int)*(oidIndex + groupNameL + contextPrefixL + 2);
 *level = (int)*(oidIndex + groupNameL + contextPrefixL + 3);

 return 0;
}