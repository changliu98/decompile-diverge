char *__cdecl func0(const char *word, char *result)
{
  char v2; // dl
  int v3; // ecx
  int v4; // ecx
  int i; // [rsp+4h] [rbp-1Ch]
  int capitalize; // [rsp+8h] [rbp-18h]
  int index; // [rsp+Ch] [rbp-14h]

  index = 0;
  capitalize = 1;
  for ( i = 0; word[i]; ++i )
  {
    if ( word[i] == 95 )
    {
      capitalize = 1;
    }
    else if ( capitalize )
    {
      v2 = toupper(word[i]);
      v3 = index++;
      result[v3] = v2;
      capitalize = 0;
    }
    else
    {
      v4 = index++;
      result[v4] = word[i];
    }
  }
  result[index] = 0;
  return result;
}