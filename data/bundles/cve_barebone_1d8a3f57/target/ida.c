int __cdecl stszin(int size)
{
  unsigned int fsize; // [rsp+Ch] [rbp-14h]
  uint32_t ofs; // [rsp+10h] [rbp-10h]
  int cnt; // [rsp+14h] [rbp-Ch]

  u32in();
  u32in();
  dword_40B0 = u32in();
  qword_40A8 = (__int64)malloc(4LL * (unsigned int)(dword_40B0 + 1));
  if ( !qword_40A8 )
    return -1;
  ofs = 0;
  *(_DWORD *)qword_40A8 = 0;
  for ( cnt = 0; cnt < (unsigned int)dword_40B0; ++cnt )
  {
    fsize = u32in();
    ofs += fsize;
    if ( dword_40B8 < fsize )
      dword_40B8 = fsize;
    *(_DWORD *)(qword_40A8 + 4LL * (cnt + 1)) = ofs;
    if ( ofs < *(_DWORD *)(qword_40A8 + 4LL * cnt) )
      return -1;
  }
  return size;
}