int __cdecl func0(int a, int b)
{
  unsigned __int64 ba; // [rsp+4h] [rbp-8h]

  HIDWORD(ba) = a;
  LODWORD(ba) = b;
  while ( (_DWORD)ba )
    ba = __PAIR64__(ba, SHIDWORD(ba) % (int)ba);
  return HIDWORD(ba);
}