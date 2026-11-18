int __cdecl func0(char **listval, int size)
{
  int i; // [rsp+8h] [rbp-18h]
  int current_val; // [rsp+Ch] [rbp-14h] BYREF
  int min_val; // [rsp+10h] [rbp-10h]
  int sizea; // [rsp+14h] [rbp-Ch]
  char **listvala; // [rsp+18h] [rbp-8h]

  listvala = listval;
  sizea = size;
  min_val = 0x7FFFFFFF;
  for ( i = 0; i < sizea; ++i )
  {
    if ( (unsigned int)__isoc99_sscanf(listvala[i], &unk_2004, &current_val) )
    {
      if ( current_val < min_val )
        min_val = current_val;
    }
  }
  return min_val;
}