char *__cdecl func0(int num)
{
  int i; // [rsp+Ch] [rbp-B4h]
  char *syb[13]; // [rsp+10h] [rbp-B0h] BYREF
  int val[13]; // [rsp+80h] [rbp-40h] BYREF
  int numa; // [rsp+BCh] [rbp-4h]

  numa = num;
  memcpy(val, &unk_2010, sizeof(val));
  memcpy(syb, &off_3D70, sizeof(syb));
  func0_roman_num = 0;
  i = 0;
  while ( numa > 0 )
  {
    while ( numa >= val[i] )
    {
      strcat(&func0_roman_num, syb[i]);
      numa -= val[i];
    }
    ++i;
  }
  return &func0_roman_num;
}