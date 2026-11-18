char *__cdecl func0(const char *str1)
{
  int lastIdx; // [rsp+Ch] [rbp-24h]
  int i; // [rsp+10h] [rbp-20h]
  int length; // [rsp+14h] [rbp-1Ch]
  int has_digit; // [rsp+1Ch] [rbp-14h]
  int has_lower; // [rsp+20h] [rbp-10h]
  int has_upper; // [rsp+24h] [rbp-Ch]

  has_upper = 0;
  has_lower = 0;
  has_digit = 0;
  length = strlen(str1);
  for ( i = 0; i < length; ++i )
  {
    if ( ((*__ctype_b_loc())[str1[i]] & 0x100) != 0 )
      has_upper = 1;
    if ( ((*__ctype_b_loc())[str1[i]] & 0x200) != 0 )
      has_lower = 1;
    if ( ((*__ctype_b_loc())[str1[i]] & 0x800) != 0 )
      has_digit = 1;
  }
  func0_result[0] = 0;
  if ( !has_upper )
    strcat(func0_result, "String must have 1 upper case character,");
  if ( !has_lower )
    strcat(func0_result, "String must have 1 lower case character,");
  if ( !has_digit )
    strcat(func0_result, "String must have 1 number,");
  if ( length < 8 )
    strcat(func0_result, "String length should be atleast 8,");
  if ( has_upper && has_lower && has_digit && length >= 8 )
  {
    strcpy(func0_result, "Valid string.");
  }
  else
  {
    lastIdx = strlen(func0_result) - 1;
    if ( func0_result[lastIdx] == 44 )
      func0_result[lastIdx] = 0;
  }
  return func0_result;
}