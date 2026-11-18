int __cdecl yuarel_split_path(char *path, char **parts, int max_parts)
{
  int v3; // ecx
  char *v4; // rax
  int i; // [rsp+0h] [rbp-20h]
  char *patha; // [rsp+10h] [rbp-10h]
  char *pathb; // [rsp+10h] [rbp-10h]

  patha = path;
  i = 0;
  if ( !path || !*path )
    return -1;
  do
  {
    while ( *patha == 47 )
      ++patha;
    if ( !*patha )
      break;
    v3 = i++;
    parts[v3] = patha;
    pathb = strchr(patha, 47);
    if ( !pathb )
      break;
    v4 = pathb;
    patha = pathb + 1;
    *v4 = 0;
  }
  while ( i < max_parts );
  return i;
}