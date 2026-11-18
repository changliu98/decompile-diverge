int __cdecl bracketed_paste(paste_mode_T mode, int drop, garray_T *gap)
{
  int v3; // eax
  bool v5; // [rsp+13h] [rbp-8Dh]
  int save_paste; // [rsp+14h] [rbp-8Ch]
  int save_allow_keys; // [rsp+18h] [rbp-88h]
  int ret_char; // [rsp+1Ch] [rbp-84h]
  char_u *end; // [rsp+20h] [rbp-80h]
  int idx; // [rsp+2Ch] [rbp-74h]
  char_u buf[86]; // [rsp+30h] [rbp-70h] BYREF
  int c; // [rsp+8Ch] [rbp-14h]
  garray_T *gapa; // [rsp+90h] [rbp-10h]
  int dropa; // [rsp+98h] [rbp-8h]
  paste_mode_T modea; // [rsp+9Ch] [rbp-4h]

  modea = mode;
  dropa = drop;
  gapa = gap;
  idx = 0;
  end = find_termcode((char_u *)&name);
  ret_char = -1;
  save_allow_keys = allow_keys;
  save_paste = p_paste;
  if ( end && strlen((const char *)end) >= 0x41 )
    end = 0LL;
  ++no_mapping;
  allow_keys = 0;
  if ( !p_paste )
    set_option_value((char_u *)"paste", 1LL, 0LL, 0);
  while ( end || vpeekc() )
  {
    do
    {
      c = vgetc();
      v5 = 1;
      if ( c != 4097 )
      {
        v5 = 1;
        if ( c != 4098 )
          v5 = c == 4099;
      }
    }
    while ( v5 );
    if ( !c || got_int || ex_normal_busy > 0 && c == 3 )
      break;
    if ( has_mbyte )
    {
      idx += mb_char2bytes((unsigned int)c, &buf[idx]);
    }
    else
    {
      v3 = idx++;
      buf[v3] = c;
    }
    buf[idx] = 0;
    if ( end && !strncmp((const char *)buf, (const char *)end, idx) )
    {
      if ( !end[idx] )
        break;
    }
    else
    {
      if ( !dropa )
      {
        switch ( modea )
        {
          case PASTE_INSERT:
            if ( stop_arrow() == 1 )
            {
              c = buf[0];
              if ( idx == 1 && (c == 13 || c == 10) )
              {
                ins_eol(c);
              }
              else
              {
                ins_char_bytes(buf, idx);
                AppendToRedobuffLit(buf, idx);
              }
            }
            break;
          case PASTE_CMDLINE:
            put_on_cmdline(buf, idx, 1);
            break;
          case PASTE_EX:
            if ( gapa && ga_grow(gapa, idx) == 1 )
            {
              memmove((char *)gapa->ga_data + gapa->ga_len, buf, idx);
              gapa->ga_len += idx;
            }
            break;
          case PASTE_ONE_CHAR:
            if ( ret_char == -1 )
            {
              if ( has_mbyte )
                ret_char = mb_ptr2char(buf);
              else
                ret_char = buf[0];
            }
            break;
          default:
            break;
        }
      }
      idx = 0;
    }
  }
  --no_mapping;
  allow_keys = save_allow_keys;
  if ( !save_paste )
    set_option_value((char_u *)"paste", 0LL, 0LL, 0);
  return ret_char;
}