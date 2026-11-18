char *__cdecl func0(const char *string)
{
  int i; // [rsp+4h] [rbp-Ch]

  for ( i = 0; string[i]; ++i )
    func0_result[i] = toupper((unsigned __int8)string[i]);
  func0_result[i] = 0;
  return func0_result;
}