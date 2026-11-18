void __cdecl gitn_box_del(GF_Box *s)
{
  u32 i; // [rsp+14h] [rbp-Ch]

  if ( s )
  {
    for ( i = 0; i < LOWORD(s[1].type); ++i )
    {
      if ( *(_QWORD *)(16LL * i + s[1].size + 8) )
        gf_free(*(void **)(16LL * i + s[1].size + 8));
    }
    if ( s[1].size )
      gf_free((void *)s[1].size);
    gf_free(s);
  }
}