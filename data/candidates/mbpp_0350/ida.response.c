int __cdecl func0(const char *s)
{
  __int64 v1; // rax
  int i_0; // [rsp+8h] [rbp-88h]
  int i; // [rsp+Ch] [rbp-84h]
  int arr[26]; // [rsp+10h] [rbp-80h] BYREF
  int n; // [rsp+80h] [rbp-10h]
  int maxOcc; // [rsp+84h] [rbp-Ch]
  const char *sa; // [rsp+88h] [rbp-8h]

  sa = s;
  maxOcc = 0;
  n = strlen(s);
  memset(arr, 0, sizeof(arr));
  for ( i = 0; i < n; ++i )
  {
    v1 = sa[i] - 97;
    ++arr[v1];
  }
  for ( i_0 = 0; i_0 < 26; ++i_0 )
  {
    if ( arr[i_0] > maxOcc )
      maxOcc = arr[i_0];
  }
  return n - maxOcc;
}