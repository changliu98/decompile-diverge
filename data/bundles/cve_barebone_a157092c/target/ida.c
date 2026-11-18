void *__cdecl get_register(int name, int copy)
{
  __int64 v2; // rcx
  int i; // [rsp+4h] [rbp-1Ch]
  yankreg_T *reg; // [rsp+8h] [rbp-18h]

  get_yank_register(name, 0);
  reg = (yankreg_T *)alloc(0x18uLL);
  if ( !reg )
    return 0LL;
  v2 = y_current;
  reg->y_array = *(char_u ***)y_current;
  reg->y_size = *(_QWORD *)(v2 + 8);
  *(_QWORD *)&reg->y_type = *(_QWORD *)(v2 + 16);
  if ( copy )
  {
    if ( reg->y_size )
      reg->y_array = (char_u **)alloc(8 * reg->y_size);
    else
      reg->y_array = 0LL;
    if ( reg->y_array )
    {
      for ( i = 0; i < reg->y_size; ++i )
        reg->y_array[i] = vim_strsave(*(char_u **)(*(_QWORD *)y_current + 8LL * i));
    }
  }
  else
  {
    *(_QWORD *)y_current = 0LL;
  }
  return reg;
}