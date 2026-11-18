char *__cdecl ft_strcpy(char *dest, char *src)
{
  int v2; // ecx
  int v3; // ecx
  int src_len; // [rsp+0h] [rbp-24h]
  int dest_len; // [rsp+4h] [rbp-20h]
  int i; // [rsp+8h] [rbp-1Ch]

  dest_len = 0;
  do
    v2 = dest_len++;
  while ( dest[v2] );
  src_len = 0;
  do
    v3 = src_len++;
  while ( src[v3] );
  i = -1;
  if ( src_len > dest_len )
    return (char *)"";
  while ( src[++i] )
    dest[i] = src[i];
  dest[i] = 0;
  return dest;
}