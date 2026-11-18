int __cdecl func0(const char *input)
{
  int v1; // eax
  int number_0; // [rsp+0h] [rbp-120h]
  int number; // [rsp+4h] [rbp-11Ch]
  int i; // [rsp+8h] [rbp-118h]
  int index; // [rsp+Ch] [rbp-114h]
  char temp[256]; // [rsp+10h] [rbp-110h] BYREF
  int max; // [rsp+114h] [rbp-Ch]
  const char *inputa; // [rsp+118h] [rbp-8h]

  inputa = input;
  max = 0;
  index = 0;
  for ( i = 0; inputa[i]; ++i )
  {
    if ( inputa[i] < 48 || inputa[i] > 57 )
    {
      if ( index )
      {
        temp[index] = 0;
        number = atoi(temp);
        if ( number > max )
          max = number;
        index = 0;
      }
    }
    else
    {
      v1 = index++;
      temp[v1] = inputa[i];
    }
  }
  if ( index )
  {
    temp[index] = 0;
    number_0 = atoi(temp);
    if ( number_0 > max )
      return number_0;
  }
  return max;
}