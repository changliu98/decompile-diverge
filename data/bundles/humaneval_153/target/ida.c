void __cdecl func0(const char *class_name, const char **extensions, int ext_count, char *output)
{
  char chr; // [rsp+7h] [rbp-49h]
  int j; // [rsp+8h] [rbp-48h]
  int strength; // [rsp+Ch] [rbp-44h]
  const char *extension; // [rsp+10h] [rbp-40h]
  int i; // [rsp+1Ch] [rbp-34h]
  const char *strongest; // [rsp+20h] [rbp-30h]
  int max_strength; // [rsp+2Ch] [rbp-24h]

  max_strength = -1000;
  strongest = 0LL;
  for ( i = 0; i < ext_count; ++i )
  {
    extension = extensions[i];
    strength = 0;
    for ( j = 0; extension[j]; ++j )
    {
      chr = extension[j];
      if ( chr >= 65 && chr <= 90 )
        ++strength;
      if ( chr >= 97 && chr <= 122 )
        --strength;
    }
    if ( strength > max_strength )
    {
      max_strength = strength;
      strongest = extensions[i];
    }
  }
  sprintf(output, "%s.%s", class_name, strongest);
}