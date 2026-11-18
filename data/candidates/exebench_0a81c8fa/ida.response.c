void __cdecl std::swap[abi:nn200000]<unsigned short>(short *a, short *b)
{
  short temp; // [rsp+0h] [rbp-12h]

  temp = *a;
  *a = *b;
  *b = temp;
}