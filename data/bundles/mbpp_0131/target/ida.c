char *__cdecl func0(char *str1)
{
  int v1; // eax
  int v2; // eax
  char v3; // dl
  int v4; // eax
  int k; // [rsp+8h] [rbp-88h]
  char char1; // [rsp+Fh] [rbp-81h]
  char vowels[100]; // [rsp+10h] [rbp-80h] BYREF
  int j; // [rsp+80h] [rbp-10h]
  int i; // [rsp+84h] [rbp-Ch]
  char *str1a; // [rsp+88h] [rbp-8h]

  str1a = str1;
  j = 0;
  memset(vowels, 0, sizeof(vowels));
  for ( i = 0; str1a[i]; ++i )
  {
    char1 = str1a[i];
    if ( strchr("aeiouAEIOU", char1) )
    {
      v1 = j++;
      vowels[v1] = char1;
    }
  }
  vowels[j] = 0;
  j = 0;
  k = strlen(vowels) - 1;
  for ( i = 0; str1a[i]; ++i )
  {
    if ( strchr("aeiouAEIOU", str1a[i]) )
    {
      v2 = k--;
      v3 = vowels[v2];
    }
    else
    {
      v3 = str1a[i];
    }
    v4 = j++;
    func0_result_string[v4] = v3;
  }
  func0_result_string[j] = 0;
  return func0_result_string;
}