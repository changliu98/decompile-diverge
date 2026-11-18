char *__cdecl func0(char *string)
{
  int index; // [rsp+4h] [rbp-41Ch]
  char *result; // [rsp+8h] [rbp-418h]
  int new_length; // [rsp+10h] [rbp-410h]
  int space_count; // [rsp+14h] [rbp-40Ch]
  int j; // [rsp+18h] [rbp-408h]
  int ja; // [rsp+18h] [rbp-408h]
  int i; // [rsp+1Ch] [rbp-404h]
  char new_string[1000]; // [rsp+20h] [rbp-400h] BYREF
  char *stringa; // [rsp+410h] [rbp-10h]

  stringa = string;
  space_count = 0;
  i = strlen(string);
  for ( j = 0; j < i; ++j )
  {
    if ( stringa[j] == 32 )
      ++space_count;
  }
  new_length = 2 * space_count + i;
  if ( new_length > 1000 )
    return (char *)"";
  index = new_length - 1;
  new_string[new_length] = 0;
  for ( ja = i - 1; ja >= 0; --ja )
  {
    if ( stringa[ja] == 32 )
    {
      new_string[index] = 48;
      new_string[index - 1] = 50;
      new_string[index - 2] = 37;
      index -= 3;
    }
    else
    {
      new_string[index--] = stringa[ja];
    }
  }
  result = (char *)malloc(new_length + 1);
  strcpy(result, new_string);
  return result;
}