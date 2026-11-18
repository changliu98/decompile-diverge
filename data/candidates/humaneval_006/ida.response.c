int *__cdecl func0(const char *paren_string, int *returnSize)
{
  int v2; // ecx
  char chr; // [rsp+7h] [rbp-29h]
  int count; // [rsp+8h] [rbp-28h]
  int i; // [rsp+Ch] [rbp-24h]
  int max_level; // [rsp+10h] [rbp-20h]
  int level; // [rsp+14h] [rbp-1Ch]
  int *all_levels; // [rsp+18h] [rbp-18h]

  all_levels = 0LL;
  level = 0;
  max_level = 0;
  count = 0;
  for ( i = 0; paren_string[i]; ++i )
  {
    chr = paren_string[i];
    if ( chr == 40 )
    {
      if ( ++level > max_level )
        max_level = level;
    }
    else if ( chr == 41 && !--level )
    {
      all_levels = (int *)realloc(all_levels, 4LL * (count + 1));
      v2 = count++;
      all_levels[v2] = max_level;
      max_level = 0;
    }
  }
  *returnSize = count;
  return all_levels;
}