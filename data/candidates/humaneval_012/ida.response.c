char *__cdecl func0(char **strings, int count)
{
  int current_length; // [rsp+Ch] [rbp-24h]
  int i; // [rsp+10h] [rbp-20h]
  int longest_length; // [rsp+14h] [rbp-1Ch]
  const char *out; // [rsp+18h] [rbp-18h]

  out = "";
  longest_length = 0;
  for ( i = 0; i < count; ++i )
  {
    current_length = strlen(strings[i]);
    if ( current_length > longest_length )
    {
      out = strings[i];
      longest_length = current_length;
    }
  }
  return (char *)out;
}