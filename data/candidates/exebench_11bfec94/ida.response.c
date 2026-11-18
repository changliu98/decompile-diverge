void __cdecl to_hex(long x, char *c)
{
  char h[16]; // [rsp+0h] [rbp-30h] BYREF
  int i; // [rsp+1Ch] [rbp-14h]
  char *ca; // [rsp+20h] [rbp-10h]
  long xa; // [rsp+28h] [rbp-8h]

  xa = x;
  ca = c;
  qmemcpy(h, "0123456789ABCDEF", sizeof(h));
  for ( i = 3; i >= 0; --i )
  {
    ca[i] = h[xa % 16];
    xa >>= 4;
  }
  ca[4] = 0;
}