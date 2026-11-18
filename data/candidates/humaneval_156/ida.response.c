void __cdecl func0(int number, char *result)
{
  int pos; // [rsp+Ch] [rbp-C4h]
  int num[13]; // [rsp+10h] [rbp-C0h] BYREF
  const char *rep[13]; // [rsp+50h] [rbp-80h] BYREF
  char *resulta; // [rsp+C0h] [rbp-10h]
  int numbera; // [rsp+CCh] [rbp-4h]

  numbera = number;
  resulta = result;
  memcpy(rep, &off_3D70, sizeof(rep));
  memcpy(num, &unk_2040, sizeof(num));
  pos = 0;
  *resulta = 0;
  while ( numbera > 0 )
  {
    while ( numbera >= num[pos] )
    {
      strcat(resulta, rep[pos]);
      numbera -= num[pos];
    }
    if ( numbera > 0 )
      ++pos;
  }
}